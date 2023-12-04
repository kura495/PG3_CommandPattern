#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <cassert>

/// <summary>
	/// CSVを読み込む
	/// </summary>
	/// <param name="filename">ファイル名</param>
	/// <returns></returns>
std::stringstream LoadCSVData(const std::string& filename);
