// SDKDll.h : SDKDll DLL 的主要標頭檔
//

#pragma once

//#ifdef _WIN64
//	#pragma comment(lib,".\\lib\\x64\\SDKDLL.lib") 
//#else
//	#pragma comment(lib,".\\lib\\x86\\SDKDLL.lib") 
//#endif

#pragma comment(lib,".\\SDKDLL.lib") 


// LED 矩陣SIZE
#define MAX_LED_ROW		 6
#define MAX_LED_COLUMN	 22

#include <windows.h>



struct KEY_COLOR {

	KEY_COLOR(BYTE _r, BYTE _g, BYTE _b): r(_r), g(_g), b(_b) {};
	KEY_COLOR() {};

	BYTE r;
	BYTE g;
	BYTE b;
};

//   設定/儲存整個LED 顏色的結構
struct COLOR_MATRIX {
	COLOR_MATRIX() {};

	KEY_COLOR KeyColor[MAX_LED_ROW][MAX_LED_COLUMN];
};

typedef void (CALLBACK * KEY_CALLBACK)(int iRow, int iColumn, bool bPressed);


//特效列舉
enum EFF_INDEX { EFF_FULL_ON = 0, EFF_BREATH = 1, EFF_BREATH_CYCLE = 2 , EFF_SINGLE = 3,  EFF_WAVE = 4, EFF_RIPPLE = 5, 
					EFF_CROSS = 6, EFF_RAIN = 7, EFF_STAR = 8, EFF_SNAKE = 9, EFF_REC = 10,

					EFF_SPECTRUM = 11, EFF_RAPID_FIRE = 12,  //mouse Eff

					EFF_MULTI_1 = 0xE0, EFF_MULTI_2 = 0xE1, EFF_MULTI_3 = 0xE2, EFF_MULTI_4 = 0xE3, 	                      
					EFF_OFF = 0xFE};
//裝置列表列舉
enum DEVICE_INDEX { DEV_MKeys_L = 0, DEV_MKeys_S = 1, DEV_MKeys_L_White = 2, DEV_MKeys_M_White = 3, DEV_MMouse_L = 4};

//裝置Layout列舉
enum LAYOUT_KEYBOARD {LAYOUT_UNINIT = 0, LAYOUT_US = 1, LAYOUT_EU = 2};


extern "C" {

///*****  系統資訊相關函式       *****//

/*
@ 函式名稱  : GetNowTime
@ 說明      : 取得目前系統時間 
@ 參數   	: 
@ 回傳      : TCHAR * : 字串指標  格式為%Y %m/%d %H:%M %S
@ 備註      : 
@ Date      : 2016/01/27 by Johnson
@*/
WCHAR * GetNowTime();

/*
@ 函式名稱  : GetNowCPUUsage
@ 說明      : 取得目前CPU使用量百分比
@ 參數   	: 
@ 回傳      : LONG : 0 ~ 100 區間整數
@ 備註      : 
@ Date      : 2016/01/27 by Johnson
@*/
LONG	GetNowCPUUsage();


/*
@ 函式名稱  : GetRamUsage
@ 說明      : 取得目前記憶體使用量百分比
@ 參數   	: 
@ 回傳      : DWORD : 0 ~ 100 區間整數
@ 備註      : 
@ Date      : 2016/01/27 by Johnson
@*/
DWORD	GetRamUsage();



/*
@ 函式名稱  : GetNowVolumePeekValue
@ 說明      : 取得目前播放中的音量值
@ 參數   	: 
@ 回傳      : float : 0 ~ 1 區間的浮點數
@ 備註      : 
@ Date      : 2016/01/27 by Johnson
@*/
float	GetNowVolumePeekValue();


///*****  Device 操作函式       *****//
/*
@ 函式名稱  : SetControlDevic
@ 說明      : 設定操作的裝置
@ 參數   	: DEVICE_INDEX: 裝置列表 DEV_MKeys_L, DEV_MKeys_S, DEV_MOUSE 三選一(目前無滑鼠) 
@ 回傳      : 
@ 備註      : 
@ Date      : 2016/01/27 by Johnson
@*/
void SetControlDevice(DEVICE_INDEX devIndex);


/*
@ 函式名稱  : IsDevicePlug
@ 說明      : 確認裝置是否插入
@ 參數   	: 
@ 回傳      : bool : true 為插入 ， false 為未插入
@ 備註      : 
@ Date      : 2016/01/27 by Johnson
@*/
bool	IsDevicePlug();


/*
@ 函式名稱  : GetDeviceLayout
@ 說明      : 回傳當前裝置所屬Layout
@ 參數   	: 
@ 回傳      : 回傳 LAYOUT_KEYBOARD列舉: 目前有三種  LAYOUT_UNINIT , LAYOUT_US , LAYOUT_EU 
@ 備註      : 
@ Date      : 2016/03/20 by Johnson
@*/
LAYOUT_KEYBOARD GetDeviceLayout();

/*
@ 函式名稱  : EnableLedControl
@ 說明      : 設定對裝置的LED 控制
@ 參數   	: bool bEnable: true 為設定為SW控制 ，false 為設定為FW控制
@ 回傳      : bool : true 為成功 ， false 為失敗
@ 備註      : 
@ Date      : 2016/01/27 by Johnson
@*/
bool EnableLedControl(bool bEnable);



/*
@ 函式名稱  : SwitchLedEffect
@ 說明      : 切換裝置的當前特效
@ 參數   	: EFF_INDEX iEffectIndex: 值為特效的索引值
@ 回傳      : bool : true 為成功 ， false 為失敗
@ 備註      : 
@ Date      : 2016/01/27 by Johnson
@*/
bool SwitchLedEffect(EFF_INDEX iEffectIndex);


/*
@ 函式名稱  : RefreshLed
@ 說明      : 將燈號設定從Buffer輸出到LED畫面
@ 參數   	: bool bAuto: false 為手動，每呼叫此指令一次，輸出到畫面一次， true為自動，任何燈號更新都會直接套用到畫面
@ 回傳      : bool : true 為成功 ， false 為失敗
@ 備註      : 
@ Date      : 2016/04/17 by Johnson
@*/
bool RefreshLed( bool bAuto = false );


/*
@ 函式名稱  : SetFullLedColor
@ 說明      : 設定整把鍵盤的LED 顏色
@ 參數   	: BYTE r :紅, BYTE g :綠 , BYTE b :藍
@ 回傳      : bool : true 為成功 ， false 為失敗
@ 備註      : 
@ Date      : 2016/01/27 by Johnson
@*/
bool SetFullLedColor(BYTE r, BYTE g, BYTE b );


/*
@ 函式名稱  : SetAllLedColor
@ 說明      : 設定鍵盤的"每個LED" 顏色
@ 參數   	: COLOR_MATRIX colorMatrix:結構，其依表LED Table填寫RGB值
@ 回傳      : bool : true 為成功 ， false 為失敗
@ 備註      : 
@ Date      : 2016/01/27 by Johnson
@*/
bool SetAllLedColor(COLOR_MATRIX colorMatrix );


/*
@ 函式名稱  : SetLedColor
@ 說明      : 設定單顆按鍵的LED顏色
@ 參數   	: int iRow: 行, int iColumn:列  BYTE r :紅, BYTE g :綠 , BYTE b :藍
@ 回傳      : bool : true 為成功 ， false 為失敗
@ 備註      : 
@ Date      : 2016/01/27 by Johnson
@*/
bool SetLedColor(int iRow, int iColumn, BYTE r, BYTE g, BYTE b );


/*
@ 函式名稱  : EnableKeyInterrupt
@ 說明      : 設定是否啟動按鍵回呼功能
@ 參數   	: bool bEnable: true 啟動 ，false 關閉
@ 回傳      : bool : true 為成功 ， false 為失敗
@ 備註      : 按鍵有按下或放開事件是會呼叫SetKeyCallBack所設定的回呼函式
@ Date      : 2016/04/23 by Johnson
@*/
bool EnableKeyInterrupt(bool bEnable);


/*
@ 函式名稱  : SetKeyCallBack
@ 說明      : 設定按鍵回呼函式
@ 參數   	: KEY_CALLBACK callback 回呼函式設定，其內容請參考KEY_CALLBACK定義
@ 回傳      : 無
@ 備註      : 
@ Date      : 2016/04/23 by Johnson
@*/

void SetKeyCallBack(KEY_CALLBACK callback );

}