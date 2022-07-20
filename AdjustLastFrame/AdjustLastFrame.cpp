#include "pch.h"

//--------------------------------------------------------------------

// デバッグ用コールバック関数。デバッグメッセージを出力する。
void ___outputLog(LPCTSTR text, LPCTSTR output)
{
	::OutputDebugString(output);
}

//--------------------------------------------------------------------

struct Track
{
	static const int32_t Voice = 0;
};

struct Check
{
	static const int32_t Enable = 0;
};

//--------------------------------------------------------------------

AviUtlInternal g_auin;

//--------------------------------------------------------------------

void voice(AviUtl::FilterPlugin* fp, AviUtl::FilterProcInfo* fpip)
{
	// ボイスの番号を取得する。
	int voice = fp->track[Track::Voice];

	if (voice)
	{
		// フォルダ名を取得する。
		TCHAR folderName[MAX_PATH] = {};
		::GetModuleFileName(fp->dll_hinst, folderName, MAX_PATH);
		::PathRemoveExtension(folderName);
		MY_TRACE_TSTR(folderName);

		// wav ファイルのパスを取得する。
		TCHAR wavFileName[MAX_PATH] = {};
		::StringCbPrintf(wavFileName, sizeof(wavFileName), _T("%s\\%d.wav"), folderName, voice);
		MY_TRACE_TSTR(wavFileName);

		// ファイルが存在するなら
		if (::GetFileAttributes(wavFileName) != INVALID_FILE_ATTRIBUTES)
		{
			// wav ファイルを再生する。
			::PlaySound(wavFileName, 0, SND_FILENAME | SND_ASYNC);
		}
	}
}

BOOL adjustLastFrame(AviUtl::FilterPlugin* fp, AviUtl::FilterProcInfo* fpip)
{
	if (!fp->check[0])
		return FALSE; // "最終フレームを自動調整する" にチェックが入っていない場合は何もしない。

	if (g_auin.GetExEditFrameNumber() == 0)
		return FALSE; // 拡張編集の最終フレーム番号が無効の場合は何もしない。

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
	HWND exeditWindow = g_auin.GetExEditWindow();

	if (!exeditWindow)
		return FALSE;

	// 「最後のオブジェクト位置を最終フレーム」コマンドをポストする。
	::PostMessage(exeditWindow, WM_COMMAND, 1097, 0);

	voice(fp, fpip);

	return TRUE;
}

//--------------------------------------------------------------------

BOOL func_init(AviUtl::FilterPlugin* fp)
{
	if (!g_auin.initExEditAddress())
		return FALSE;

	return TRUE;
}

BOOL func_exit(AviUtl::FilterPlugin* fp)
{
	return FALSE;
}

BOOL func_proc(AviUtl::FilterPlugin* fp, AviUtl::FilterProcInfo* fpip)
{
	return adjustLastFrame(fp, fpip);
}

//--------------------------------------------------------------------

LPCSTR track_name[] =
{
	"ﾎﾞｲｽ",
};

int track_def[] = {  1 };
int track_min[] = {  0 };
int track_max[] = { 10 };

static LPCSTR check_name[] =
{
	"最終フレームを自動調整する",
};
static int check_def[] =
{
	TRUE,
};

EXTERN_C AviUtl::FilterPluginDLL* CALLBACK GetFilterTable()
{
	LPCSTR name = "最終フレーム自動調整";
	LPCSTR information = "最終フレーム自動調整 2.2.0 by 蛇色";

	static AviUtl::FilterPluginDLL filter =
	{
		.flag =
			AviUtl::detail::FilterPluginFlag::AlwaysActive |
			AviUtl::detail::FilterPluginFlag::DispFilter |
			AviUtl::detail::FilterPluginFlag::ExInformation,
		.name = name,
		.track_n = sizeof(track_name) / sizeof(*track_name),
		.track_name = track_name,
		.track_default = track_def,
		.track_s = track_min,
		.track_e = track_max,
		.check_n = sizeof(check_name) / sizeof(*check_name),
		.check_name = check_name,
		.check_default = check_def,
		.func_proc = func_proc,
		.func_init = func_init,
		.func_exit = func_exit,
		.information = information,
	};

	return &filter;
}

//--------------------------------------------------------------------
