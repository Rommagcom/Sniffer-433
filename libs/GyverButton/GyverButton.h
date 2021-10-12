#pragma once
#include <Arduino.h>

/*
	GyverButton - ���������� ��� ������������������� ��������� ������� ������. �����������:
	- ������ � ��������� ���������� � ��������� ������������ ��������
	- ������ � ������������ PULL_UP � PULL_DOWN
	- ����� ������ � ����������� ������������� ��������� (������������� �����)	
	- ��������� �������, �����������, ����������, ����� �� ������ (+ ��������� ���������)	
	- ��������� ����������, �������� � �������� ������� (�������� ��������)
	- ��������� ������ ���������� ������� ������ (������� ���������� ���������� �������)	
	- ������� ��������� �������� ���������� � �������� ����� � �������� ���������� �� �������
	- ����������� ������ � "������������" �������� (��� ����������� ���������� ������������ ��� ��������� � ����������� ���������)
	
	������������ ����� �����: https://alexgyver.ru/gyverbutton/
	��� ����������� �������� ������ ������ ������������� ������������ ���� GyverCore https://alexgyver.ru/gyvercore/
	
	������ 2.14 �� 09.09.2019:	
	- ���������� �������
	
	������ 2.15
	- ��������� ����������� �������� ������ ��� �������� � ����
	
	������ 3.0
	- ������� � ������������� ���, ���������� �������������, ��������� �������
	
	������ 3.1
	- isStep ����� ��������� ���������� ������, ��������� ����� ��� (��. ������ clicks_step)
	
	������ 3.2
	- �������� ����� getHoldClicks() - ������� ���������� ������, �������������� �����������
*/

#pragma pack(push,1)
typedef struct {		
	bool btn_deb: 1;	
	bool hold_flag: 1;
	bool counter_flag: 1;
	bool isHolded_f: 1;
	bool isRelease_f: 1;
	bool isPress_f: 1;
	bool step_flag: 1;
	bool oneClick_f: 1;
	bool isOne_f: 1;
	bool inv_state: 1;
	bool mode: 1;
	bool type: 1;
	bool tickMode: 1;
	bool noPin: 1;
} GyverButtonFlags;
#pragma pack(pop)

#define BTN_NO_PIN -1
#define HIGH_PULL 0
#define LOW_PULL 1
#define NORM_OPEN 0
#define NORM_CLOSE 1
#define MANUAL 0
#define AUTO 1

// �������� �������������:
// GButton btn;							// ��� �������� � ���� (����������� ������) � ��� �������� ���� (�� �����. HIGH_PULL � NORM_OPEN)
// GButton btn(���);					// � ��������� � ���� � ��� �������� ���� (�� �����. HIGH_PULL � NORM_OPEN)
// GButton btn(���, ��� �������.);		// � ��������� � ���� � ��������� ���� ����������� (HIGH_PULL / LOW_PULL) � ��� �������� ���� ������ (�� �����. NORM_OPEN)
// GButton btn(���, ��� �������., ��� ������);			// � ��������� � ���� � ��������� ���� ����������� (HIGH_PULL / LOW_PULL) � ���� ������ (NORM_OPEN / NORM_CLOSE)
// GButton btn(BTN_NO_PIN, ��� �������., ��� ������);	// ��� �������� � ���� � ��������� ���� ����������� (HIGH_PULL / LOW_PULL) � ���� ������ (NORM_OPEN / NORM_CLOSE)

class GButton {
  public:
	GButton(int8_t pin = BTN_NO_PIN, uint8_t type = HIGH_PULL, uint8_t dir = NORM_OPEN);	// ����������� ������, ��������� PIN ���, ��� type (HIGH_PULL / LOW_PULL) � ����������� dir (NORM_OPEN / NORM_CLOSE)
														// HIGH_PULL - ������ ���������� � GND, ��� �������� � VCC, pinMode - INPUT_PULLUP (�� ���������)
														// LOW_PULL - ������ ���������� � VCC, ��� �������� � GND, pinMode - INPUT
														// NORM_OPEN - ������ �� ��������� ���������� (�� ���������)
														// NORM_CLOSE - ������ �� ��������� ��������
	
	void setDebounce(uint16_t debounce);				// ��������� ������� ������������ (�� ��������� 80 ��)
	void setTimeout(uint16_t timeout);					// ��������� �������� ��������� (�� ��������� 300 ��)
	void setClickTimeout(uint16_t timeout);				// ��������� �������� ����� ������� (�� ��������� 500 ��)	
	void setStepTimeout(uint16_t step_timeout);			// ��������� �������� ����� ������������ (�� ��������� 400 ��)	
	void setType(uint8_t type);							// ��������� ���� ������ (HIGH_PULL - ��������� � �������, LOW_PULL - � gnd)	
	void setDirection(uint8_t dir);						// ��������� ����������� (����������/�������� �� ��������� - NORM_OPEN, NORM_CLOSE)	
	
	void setTickMode(uint8_t tickMode);					// (MANUAL / AUTO) ������ ��� �������������� ����� ������ �������� tick()	
														// MANUAL - ����� �������� ������� tick() �������														
														// AUTO - tick() ������ �� ��� ��������� ������� � ������������ ����
	
	void tick();										// ����� ������	
	void tick(boolean state);							// ����� �������� �������� (0 ������, 1 �� ������) (��� ���������, ����������� ��������� � ����������)
	
	boolean isPress();		// ���������� true ��� ������� �� ������. ������������ ����� ������
	boolean isRelease();	// ���������� true ��� ���������� ������. ������������ ����� ������
	boolean isClick();		// ���������� true ��� �����. ������������ ����� ������
    boolean isHolded();		// ���������� true ��� ��������� ������ timeout. ������������ ����� ������
	boolean isHold();		// ���������� true ��� ������� ������, �� ������������
	boolean state();		// ���������� ��������� ������

	boolean isSingle();		// ���������� true ��� ��������� �����. ������������ ����� ������
	boolean isDouble();		// ���������� true ��� ������� �����. ������������ ����� ������
	boolean isTriple();		// ���������� true ��� ������� �����. ������������ ����� ������
	
	boolean hasClicks();	// �������� �� ������� ������. ������������ ����� ������
	uint8_t getClicks();	// ������� ���������� ������
	uint8_t getHoldClicks();// ������� ���������� ������, �������������� �����������
	
	boolean isStep(byte clicks = 0); // ���������� true �� ������� setStepTimeout, ������ ������
	
  private:
    GyverButtonFlags flags;
    uint8_t _PIN = 0;
	uint16_t _debounce = 60;
	uint16_t _timeout = 500;
	uint16_t _click_timeout = 500;
	uint16_t _step_timeout = 400;
	uint8_t btn_counter = 0, last_counter = 0, last_hold_counter = 0;
	uint32_t btn_timer = 0;	
	bool btn_state = false;
	bool btn_flag = false;
};