#include "MOTOR_DC.h"
#include "SW.h"
#include "IO.h"
#include "RAM.h"

volatile int32_t Pulse, pre_Pulse;
volatile int32_t rSpeed, Err, pre_Err; /* for speed control */
volatile int32_t pPart = 0, iPart = 0, dPart = 0; /* PID gains */
volatile int32_t Ctrl_Speed = 5; /* van toc can dieu khien */
volatile int32_t Output;
volatile unsigned char sample_count = 0;

void stop_Motor()
{
	if (!TSTFLAG(g_bF_SW1_Status) || !TSTFLAG(g_bF_SW2_Status))
	{
		IOPort_Write(D_4, 0);
		IOPort_Write(D_5, 0);
	}
}

void open_Door()
{
	IOPort_Write(D_4, 1);
	IOPort_Write(D_5, 0);
}

void close_Door()
{
	IOPort_Write(D_4, 0);
	IOPort_Write(D_5, 1);
}

void motor_Speed(int32_t des_speed)
{
	rSpeed = Pulse - pre_Pulse; /* tinh van toc (trong sampleing time) */
	pre_Pulse = Pulse; /* luu lai gia tri Pulse: so xung */
	Err = des_speed - abs(rSpeed); /* tinh error */
								   /* cac thanh phan PID */
	pPart = g_Kp * Err;
	dPart = g_Kd * (Err - pre_Err)*inv_Sampling_time;
	iPart += g_Ki * Sampling_time*Err / 1000;
	Output += pPart + dPart + iPart; /* cong thuc duoc bien doi vi la dieu khien van toc (saturation) */
	if (Output >= PWM_Period) Output = PWM_Period - 1;
	if (Output <= 0) Output = 1;
	OCR1A = Output; /* gan duty cycle cho OCR1A: update PWM */
	pre_Err = Err; /* luu lai gia tri error */
}

void rotate()
{
	Pulse = 0;
	/* Encoder va cac chan nhap toc do */
	DDRB |= (1<<D_6); /* set PORTB as a input port to use the T0 input pin and INT2 */
	//PORTB = 0xFF; /* dien tro keo len (nhat la encoder) */
				  /* Motor */
	MOTOR_DDR = 0xF0;
	sbi(MOTOR_PORT, MOTOR_DIR);
	/* ngat ngoai cho encoder */
	MCUCR |= 0x08; /* ngat INT1 la ngat canh xuong - Falling Edge */
	SREG |= (1 << INT1); /* enable INT1 */
						 /* dung timer 2 lam bo dinh thoi 25ms, sampling time */
	TCCR2A |= (1 << CS22) | (1 << CS21) | (1 << CS20); /* prescaler=1024 */
	TCNT2 = 60; /* gan khoi tao de duoc 25ms */
	TIMSK2 = (1 << TOIE2);
	/* dung timer1 lam PWM generator */
	/* prescaler = 1024, P_clock=16mhz/1024=15,625 khz, Tần số xung F_pwm=15,625 khz/256=61,0351 hz */
	TCCR1A |= (1 << WGM01) | (1 << WGM00) | (1 << COM0A1); /* (1 << COM1A1) | (1 << COM1B1) | (WGM11); */
	TCCR1B |= (1 << CS02) | (1 << CS00); /* (1 << WGM13) | (1 << WGM12) | (1 << CS10) */

	/* khoi dong gia tri PWM */
	OCR1A = 1; /* do rong PWM 1/255 */
	ICR1 = PWM_Period;
	sbi(MOTOR_PORT, MOTOR_EN); /* start motor */
	sei();

	/*-------------*/
	while (1)
	{
		if (sample_count >= 10)
		{
			Ctrl_Speed = (PINB >> 4) & 0x0F;
			//Serial.println(rSpeed);
			//Serial.print("van toc mong muon: ");
			//Serial.println(Ctrl_Speed);
			sample_count = 0;
		}
	}
}

ISR(TIMER2_OVF_vect)
{
	TCNT2 = 60;
	sample_count++;
	motor_Speed(Ctrl_Speed);
}

//ISR(INT1_vect)
//{
//	if (bit_is_set(PINB, 0)) Pulse++;
//	else Pulse--;
//}