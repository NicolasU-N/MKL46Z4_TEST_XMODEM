/* Tiempo.c    Implementacion del modulo de tiempo */

#include "Tiempo.h"

/* Rutina para iniciar el módulo (su estructura de datos) */
void Tm_Inicio(Tm_Control *tcp, Tm_Periodo *pp, Tm_Num nper, Tm_Timeout *tp,
		Tm_Num nto, Tm_Pwm *ppwm, Tm_Num npwm, Tm_Atender *atender) { //
	Tm_Num i;

	/* Tabla de períodos */
	tcp->pp = pp;
	tcp->nper = nper;
	for (i = nper; i; ++pp, --i) {
		pp->banderas = 0;
		pp->contador = pp->periodo = 0;
	}

	//Tabla de pwms
	tcp->ppwm = ppwm;
	tcp->npwm = npwm;
	for (i = npwm; i; ++ppwm, --i) {
		ppwm->num_puerto = 0;
		//ppwm->puerto = 0;
		ppwm->contador = ppwm->cmp = ppwm->periodo = 0;
	}

	/* Tabla de timeouts/retardos */
	tcp->tp = tp;
	tcp->nto = nto;
	for (i = nto; i; ++tp, --i)
		(*tp) = 0;

	/* Rutina para manejar el timer (HW) */
	tcp->atender = atender;
}

/* Rutina para procesar el módulo (dentro del loop de polling) */
void Tm_Procese(Tm_Control *tcp) {
	Tm_Num i;
	Tm_Periodo *pp;
	Tm_Pwm *ppwm;
	Tm_Timeout *tp;

	if (!(tcp->atender(SI)))
		return;

	//myprintf("dentro de procese timer\n");

	/* Procesa la tabla de períodos */
	for (i = tcp->nper, pp = tcp->pp; i; ++pp, --i)
		if (pp->banderas & TM_PER_F_ACTIVO) { /* El período está activo: se procesa */
			--(pp->contador);
			if (!(pp->contador)) { /* Fin de conteo: activa la bandera y reinicia el contador */
				pp->banderas |= TM_PER_F_FC;
				pp->contador = pp->periodo;
			}
		}

	/* Procesa la tabla de pwms*/
	for (i = tcp->npwm, ppwm = tcp->ppwm; i; ++ppwm, --i) {
		--(ppwm->contador);
		if (!(ppwm->contador)) { //	Fin de conteo: activa la bandera y reinicia el contador
			//Encender Led
			PTD->PCOR |= (1u << ppwm->num_puerto); // ON
			ppwm->contador = ppwm->periodo;
		} else if (ppwm->contador == ppwm->cmp) {
			PTD->PSOR |= (1u << ppwm->num_puerto); // OFF
		}
	}

	/* Procesa la tabla de timeouts/retardos */
	for (i = tcp->nto, tp = tcp->tp; i; ++tp, --i)
		if (*tp)
			/* Aun o está en 0: sigue decrementando */
			--(*tp);
}

/* ===== RUTINAS DE INTERFAZ ====== */
/* Configurar un período para que empiece a funcionar */
char Tm_Inicie_periodo(Tm_Control *tcp, Tm_Num num_periodo, Tm_Contador periodo) {
	Tm_Periodo *pp;

	if (num_periodo >= tcp->nper)
		return NO;

	pp = tcp->pp + num_periodo;
	pp->banderas = TM_PER_F_ACTIVO; /* Lo activa pero al mismo borra las otras banderas que pueda
	 haber; puede que se desee cambiar esto para un comportamiento
	 diferente */
	pp->contador = pp->periodo = periodo;

	return SI;
}

/* Desactivar un período para que deje de funcionar */
void Tm_Termine_periodo(Tm_Control *tcp, Tm_Num num_periodo) {
	Tm_Periodo *pp;

	if (num_periodo >= tcp->nper)
		return;

	pp = tcp->pp + num_periodo;
	pp->banderas = 0; /* Lo desactiva pero al mismo borra las otras banderas que pueda haber; puede
	 que se desee cambiar esto para un comportamiento diferente */
	pp->contador = pp->periodo = 0; /* Esto no es necesario, pero es prudente. */
}

/* Verificar si hubo fin de conteo en un periodo */
char Tm_Hubo_periodo(Tm_Control *tcp, Tm_Num num_periodo) {
	if (num_periodo >= tcp->nper)
		return NO;

	return (tcp->pp[num_periodo].banderas & TM_PER_F_FC);
}

/* Bajar la bandera de conteo en un periodo */
void Tm_Baje_periodo(Tm_Control *tcp, Tm_Num num_periodo) {
	if (num_periodo >= tcp->nper)
		return;

	tcp->pp[num_periodo].banderas &= ~TM_PER_F_FC;
}

//----------------------------------------------
/* Configurar un timeout/retardo para que empiece a funcionar */
char Tm_Inicie_timeout(Tm_Control *tcp, Tm_Num num_timeout, Tm_Contador espera) {
	if (num_timeout >= tcp->nto)
		return NO;

	tcp->tp[num_timeout] = espera;

	return SI;
}

/* Desactivar un timeout/retardo para que deje de funcionar */
void Tm_Termine_timeout(Tm_Control *tcp, Tm_Num num_timeout) {
	if (num_timeout >= tcp->nto)
		return;

	tcp->tp[num_timeout] = 0;
}

/* Verificar si hubo timeout (o se completo el retardo) */
char Tm_Hubo_timeout(Tm_Control *tcp, Tm_Num num_timeout) {
	if (num_timeout >= tcp->nto)
		return NO;

	return (tcp->tp[num_timeout] == 0);
}

//----------------------------------------------
// Configurar un pwm para que empiece a funcionar
char Tm_Inicie_pwm(Tm_Control *tcp, Tm_Num num_pwm, Tm_Contador periodo,
		Tm_Contador cmp, Tm_Num num_puerto) { //, GPIO_Type *puerto

	Tm_Pwm *ppwm;

	if (num_pwm >= tcp->npwm)
		return NO;

	ppwm = tcp->ppwm + num_pwm;
	ppwm->num_puerto = num_puerto;

	ppwm->cmp = cmp;
	ppwm->contador = ppwm->periodo = periodo;

	return SI;
}

///Desactivar un período para que deje de funcionar
char Tm_Termine_pwm(Tm_Control *tcp, Tm_Num num_pwm) {
	Tm_Pwm *ppwm;

	if (num_pwm >= tcp->npwm)
		return NO;

	ppwm = tcp->ppwm + num_pwm;
	ppwm->contador = ppwm->cmp = ppwm->periodo = 0; //Esto no es necesario, pero es prudente.
}

/* Verificar si hubo fin de conteo en un periodo */
//char Tm_Hubo_pwm(Tm_Control *tcp, Tm_Num num_pwm) {
//}
