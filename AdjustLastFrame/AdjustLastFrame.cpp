#include "pch.h"

auls::CMemref g_memref;

BOOL adjustLastFrame(FILTER *fp, FILTER_PROC_INFO *fpip)
{
	// 現在編集中のシーンのインデックスを取得する。
	int scene = g_memref.Exedit_SceneDisplaying();

	// 現在編集中のシーンの中で最も後ろにあるオブジェクト位置を取得する。
	int frameEndNumber = -1000;
	{
		auls::EXEDIT_OBJECT** objects = g_memref.Exedit_SortedObjectTable();

		for (int i = 0; objects[i]; i++)
		{
			if (scene != objects[i]->scene_set)
				continue; // 現在のシーン内のオブジェクトではなかった。

			frameEndNumber = yulib::Max(frameEndNumber, objects[i]->frame_end);
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
	HWND exeditWindow = auls::Exedit_GetWindow(fp);

	if (!exeditWindow)
		return FALSE;
#if 0
	fp->exfunc->set_frame_n(fpip->editp, frameEndNumber);
#elif 1
//	::OutputDebugString(_T("::PostMessage(exeditWindow, WM_COMMAND, 1097, 0)\n"));
	::PostMessage(exeditWindow, WM_COMMAND, 1097, 0);
#else
	static BOOL locked = FALSE; // 念の為、再帰呼び出しを防止する。

	if (!locked)
	{
		locked = TRUE;
		// "最後のオブジェクト位置を最終フレーム" コマンドを発行する。
		::SendMessage(exeditWindow, WM_COMMAND, 1097, 0);
		locked = FALSE;
	}
#endif
	return TRUE;
}

//---------------------------------------------------------------------
//		フィルタ構造体のポインタを渡す関数
//---------------------------------------------------------------------
EXTERN_C FILTER_DLL __declspec(dllexport) * __stdcall GetFilterTable(void)
{
	static TCHAR g_filterName[] = TEXT("最終フレーム自動調整");
	static TCHAR g_filterInformation[] = TEXT("最終フレーム自動調整 version 1.0.2 by 蛇色");

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
	return g_memref.Init(fp); // auls::CMemref の初期化。
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
