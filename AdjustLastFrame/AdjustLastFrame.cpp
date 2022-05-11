#include "pch.h"

AviUtlInternal g_auin;

BOOL adjustLastFrame(FILTER *fp, FILTER_PROC_INFO *fpip)
{
	// 現在編集中のシーンのインデックスを取得する。
	int scene = g_auin.GetCurrentSceneIndex();

	// 現在編集中のシーンの中で最も後ろにあるオブジェクト位置を取得する。
	int frameEndNumber = -1000;
	{
		// オブジェクトの個数を取得する。
		int c = g_auin.GetCurrentSceneObjectCount();

		for (int i = 0; i < c; i++)
		{
			// オブジェクトを取得する。
			ExEdit::Object* object = g_auin.GetSortedObject(i);

			if (scene != object->scene_set)
				continue; // 現在のシーン内のオブジェクトではなかった。

			frameEndNumber = max(frameEndNumber, object->frame_end);
		}
	}

	// 最終フレーム位置を取得する。
	int frameMaxNumber = fp->exfunc->get_frame_n(fpip->editp);

	// 最終オブジェクト位置が小さすぎる場合は何もしない。
	if (frameEndNumber <= 0)
		return FALSE;

	// 最終オブジェクト位置が最終フレーム位置より大きい場合は何もしない。
	if (frameEndNumber + 1 >= frameMaxNumber)
		return FALSE;

	// 拡張編集ウィンドウを取得する。
	HWND exeditWindow = g_auin.GetExeditWindow();

	if (!exeditWindow)
		return FALSE;

	// 「最後のオブジェクト位置を最終フレーム」コマンドをポストする。
	::PostMessage(exeditWindow, WM_COMMAND, 1097, 0);

	return TRUE;
}

//---------------------------------------------------------------------
//		フィルタ構造体のポインタを渡す関数
//---------------------------------------------------------------------
EXTERN_C FILTER_DLL __declspec(dllexport) * __stdcall GetFilterTable(void)
{
	static TCHAR g_filterName[] = TEXT("最終フレーム自動調整");
	static TCHAR g_filterInformation[] = TEXT("最終フレーム自動調整 2.0.0 by 蛇色");

	static FILTER_DLL g_filter =
	{
		FILTER_FLAG_NO_CONFIG |
		FILTER_FLAG_ALWAYS_ACTIVE |
		FILTER_FLAG_DISP_FILTER |
		FILTER_FLAG_EX_INFORMATION,
		0, 0,
		g_filterName,
		NULL, NULL, NULL,
		NULL, NULL,
		NULL, NULL, NULL,
		func_proc,
		func_init,
		func_exit,
		NULL,
		NULL,
		NULL, NULL,
		NULL,
		NULL,
		g_filterInformation,
		NULL, NULL,
		NULL, NULL, NULL, NULL,
		NULL,
	};

	return &g_filter;
}

//---------------------------------------------------------------------
//		初期化
//---------------------------------------------------------------------
BOOL func_init(FILTER *fp)
{
	return g_auin.init();
}

//---------------------------------------------------------------------
//		終了
//---------------------------------------------------------------------
BOOL func_exit(FILTER *fp)
{
	return FALSE;
}

//---------------------------------------------------------------------
//		メイン処理
//---------------------------------------------------------------------
BOOL func_proc(FILTER *fp, FILTER_PROC_INFO *fpip)
{
	return adjustLastFrame(fp, fpip);
}
