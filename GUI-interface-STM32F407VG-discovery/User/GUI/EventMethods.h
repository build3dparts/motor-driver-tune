#ifndef __EVENT_METHODS__
#define __EVENT_METHODS__

#include "WindowID.h"
#include "Component.h"
#include "GUI.h"
#include "GUIButton.h"
#include "GUILabel.h"
#include "GUIEditBox.h"
#include "GUITextField.h"
#include "GUIProgress.h"
#include "GUIListbox.h"
#include "GUISlider.h"

extern double lensum;
extern bool job_start;
extern bool enc_test;
extern int senzor_rotatie_presa;
extern int senzor_material_iesire;
extern int numar_bucati;
extern int lungime_buc;
extern int bucata_curenta;
extern int hours_left;
extern int minutes_left;
extern int seconds_left;
extern GUI *current_gui_for_timer;

typedef struct _fingers_tiimng{
	char data;
	int timing;
}fingers_timing;



//keyboard predefinit pentru fereastra cu alesul numarului de bucati
void mini_predefined_keyboard1(void *interfata);
//keyboard predefinit pentru fereastra cu alesul lungimii unei bucato
void mini_predefined_keyboard2(void *interfata);
//keyboard predefinit pentru fereastra cu introducerea parolei pentur meniul de configurare
void mini_predefined_keyboard3(void *interfata);
//adauga 20 butoane predefinite pe ferestrele de ales numarul de bucati sau lungimea unei bucati
void AddPredefinedButtons(GUI *gui,int first_ID,OnEvent proc,int *label_vector,int window);
//adauga 10 butoane predefinite pe fereastra cu introdus parola pentru meniul de configurare
void AddPredefinedButtonsPWD(GUI *gui,int first_ID,OnEvent proc,int window);

//initializeaza componentele pe fereasstra [window]
void InitWindow(GUI *gui,int window);


void auto_config(void *interfata);
void motor_test(void *interfata);
void usart_interface(void *interfata);
void manual_config(void *interfata);

void move_left(void *interfata);
void move_right(void *interfata);
void testare_back(void *interfata);
void configs(void *interface);
void enpwm(void *interface);
void dispwm(void *interface);
void endrv(void *interface);
void disdrv(void *interface);
void enrst(void *interface);
void disrst(void *interface);
void enslp(void *interface);
void disslp(void *interface);
void onestep(void *interface);
void incspeed(void *interface);
void decspeed(void *interface);
void direction(void *interfata);

void slide_event(void *interfata);
void testare_back2(void *interfata);
void configs2(void *interface);

void sim_auto(void *interfata);
void sim_manual(void *interfata);
void back_sim(void *interfata);

void back_from_auto(void *interfata);
void back_from_manual(void *interfata);
void back_from_play(void *interfata);

void trace_drt(void *interfata);
void trace_stg(void *interfata);

void back_from_move(void *interfata);
void back_from_touch(void *interfata);

void back_from_vd(void *interfata);
void back_from_vs(void *interfata);

void s200(void *interfata);
void s400(void *interfata);
void s800(void *interfata);
void s1600(void *interfata);
void s3200(void *interfata);

void ProcesariFerestre(void *data);


#endif