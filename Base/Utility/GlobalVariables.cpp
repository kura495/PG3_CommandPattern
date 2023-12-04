#include"GlobalVariables.h"
GlobalVariables* GlobalVariables::GetInstance()
{
	static GlobalVariables instance;
	return &instance;
}

void GlobalVariables::CreateGroup(const std::string& groupName)
{
	//指定名のオブジェクトがなければ追加する
	datas_[groupName];
}

void GlobalVariables::Update()
{
	//メニューバーを作る
	if (!ImGui::Begin("GlobalVariables", nullptr, ImGuiWindowFlags_MenuBar)) {
		ImGui::End();
		return;
	}
	if (!ImGui::BeginMenuBar())return;
	//各グループごとに行う処理をfor文でdatas_が終わりにつくまでやる
	for (std::map<std::string, Group>::iterator itGroup = datas_.begin(); itGroup != datas_.end(); ++itGroup) {
		//グループ名を取得 itGroup->first = キー
		const std::string& groupName = itGroup->first;
		//グループの参照を取得　itGroup->second = 値
		Group& group = itGroup->second;
		//グループのメニューを追加する処理
		if (!ImGui::BeginMenu(groupName.c_str()))continue;

		//各グループの各アイテムごとに行う処理をfor文でやる
		for (std::map<std::string, Item>::iterator itItem = group.items.begin(); itItem != group.items.end(); ++itItem) {
			//アイテム名を取得(floatやVector3などの名前)
			const std::string& itemName = itItem->first;
			//アイテムの値を取得
			Item& item = itItem->second;

			//アイテム名によって分岐する
			//int32_t型の値を所持していたら
			if (std::holds_alternative<int32_t>(item.value)) {
					int32_t* ptr = std::get_if<int32_t>(&item.value);
					ImGui::SliderInt(itemName.c_str(), ptr, 0, 100);
				}
			//float型の値を所持していたら
			else if (std::holds_alternative<float>(item.value)) {
					float* ptr = std::get_if<float>(&item.value);
					ImGui::InputFloat(itemName.c_str(), ptr, 0, 100);
				}
			//Vector3型の値を所持していたら
			else if (std::holds_alternative<Vector3>(item.value)) {
					Vector3* ptr = std::get_if<Vector3>(&item.value);
					ImGui::SliderFloat3(itemName.c_str(), reinterpret_cast<float*>(ptr), -10, 10);
				}
			//読み込んだ型がItem構造体にない時とか
			else {
					assert(false);
				}
		}
		//改行をする
		ImGui::Text("\n");
		//ボタンを押すとフォルダの中にファイルができる(もとからあるときは上書き)
		//メッセージも出る
		if (ImGui::Button("Save")) {
			SaveFile(groupName);
			std::string message = std::format("{}.json saved.", groupName);
			MessageBoxA(nullptr, message.c_str(), "GlobalVariables", 0);
		}
		ImGui::EndMenu();
	}
	ImGui::EndMenuBar();
	ImGui::End();
}

//値がなければ、SetValueを呼ぶ関数たち(すでに値があるときは呼ばない)
#pragma region AddItem
void GlobalVariables::AddItem(const std::string& groupName, const std::string& key, int32_t value)
{
	//グループの参照を取得
	Group& group = datas_[groupName];
	//アイテムが未登録なら
	if (!group.items.contains(key)) {
		SetValue(groupName, key, value);
	}
}
void GlobalVariables::AddItem(const std::string& groupName, const std::string& key, float value)
{
	//グループの参照を取得
	Group& group = datas_[groupName];
	//アイテムが未登録なら
	if (!group.items.contains(key)) {
		SetValue(groupName, key, value);
	}
}
void GlobalVariables::AddItem(const std::string& groupName, const std::string& key, const Vector3& value)
{
	//グループの参照を取得
	Group& group = datas_[groupName];
	//アイテムが未登録なら
	if (!group.items.contains(key)) {
		SetValue(groupName, key, value);
	}
}
//void GlobalVariables::AddItem(const std::string& groupName, const std::string& key, const bool& value)
//{
//	//グループの参照を取得
//	Group& group = datas_[groupName];
//	//アイテムが未登録なら
//	if (!group.items.contains(key)) {
//		SetValue(groupName, key, value);
//	}
//}
#pragma endregion AddItem
//実際に値を入れる関数たち
#pragma region SetValue
void GlobalVariables::SetValue(const std::string& groupName, const std::string& key, int32_t value)
{
	//グループの参照を取得
	Group& group = datas_[groupName];
	//新しい項目のデータを設定
	Item newItem{};
	newItem.value = value;
	//設定した項目をstd::mapに追加
	group.items[key] = newItem;
}
void GlobalVariables::SetValue(const std::string& groupName, const std::string& key, float value)
{
	//グループの参照を取得
	Group& group = datas_[groupName];
	//新しい項目のデータを設定
	Item newItem{};
	newItem.value = value;
	//設定した項目をstd::mapに追加
	group.items[key] = newItem;
}
void GlobalVariables::SetValue(const std::string& groupName, const std::string& key,const Vector3& value)
{
	//グループの参照を取得
	Group& group = datas_[groupName];
	//新しい項目のデータを設定
	Item newItem{};
	newItem.value = value;
	//設定した項目をstd::mapに追加
	group.items[key] = newItem;
}
//void GlobalVariables::SetValue(const std::string& groupName, const std::string& key,const bool& value)
//{
//	//グループの参照を取得
//	Group& group = datas_[groupName];
//	//新しい項目のデータを設定
//	Item newItem{};
//	newItem.value = value;
//	//設定した項目をstd::mapに追加
//	group.items[key] = newItem;
//}

#pragma endregion  SetValue

#pragma region Getter
int32_t GlobalVariables::GetIntValue(const std::string& groupName, const std::string& key) const
{
	//グループがあるか見てみる　なければアサ―ト
	assert(datas_.contains(groupName));
	//グループの参照を取得
	const Group& group = datas_.at(groupName);
	//指定したグループに指定したキーが存在する
	assert(group.items.contains(key));

	return std::get<int32_t>(group.items.at(key).value);
}
float GlobalVariables::GetfloatValue(const std::string& groupName, const std::string& key) const
{
	//グループがあるか見てみる　なければアサ―ト
	assert(datas_.contains(groupName));
	//グループの参照を取得
	const Group& group = datas_.at(groupName);
	//指定したグループに指定したキーが存在する
	assert(group.items.contains(key));

	return std::get<float>(group.items.at(key).value);
}
Vector3 GlobalVariables::GetVector3Value(const std::string& groupName, const std::string& key) const
{
	//グループがあるか見てみる　なければアサ―ト
	assert(datas_.contains(groupName));
	//グループの参照を取得
	const Group& group = datas_.at(groupName);
	//指定したグループに指定したキーが存在する
	assert(group.items.contains(key));

	return std::get<Vector3>(group.items.at(key).value);
}
//bool GlobalVariables::GetboolValue(const std::string& groupName, const std::string& key) const
//{
//	//グループがあるか見てみる　なければアサ―ト
//	assert(datas_.contains(groupName));
//	//グループの参照を取得
//	const Group& group = datas_.at(groupName);
//	//指定したグループに指定したキーが存在する
//	assert(group.items.contains(key));
//
//	return std::get<bool>(group.items.at(key).value);
//}
#pragma endregion Getter

void GlobalVariables::SaveFile(const std::string& groupName)
{
	//グループを検索する
	std::map<std::string, Group>::iterator itGroup = datas_.find(groupName);
	//グループが存在するかどうかチェック
	assert(itGroup != datas_.end());
	//変数
	json root;
	//json::objectはstd::mapみたいなもの
	root = json::object();
	//jsonオブジェクト登録する
	root[groupName] = json::object();
	//各グループの各アイテムごとに行う処理をfor文でやる
	for (std::map<std::string, Item>::iterator itItem = itGroup->second.items.begin(); itItem != itGroup->second.items.end(); ++itItem) {
		//アイテム名を取得(floatやVector3などの名前)
		const std::string& itemName = itItem->first;
		//アイテムの値を取得
		Item& item = itItem->second;
		//アイテム名によって分岐する
		//int32_t型の値を所持していたら
		if (std::holds_alternative<int32_t>(item.value)) {
			//int32_t型の値を登録
			root[groupName][itemName] = std::get<int32_t>(item.value);
		}
		//float型の値を所持していたら
		else if (std::holds_alternative<float>(item.value)) {
			//float型の値を登録
			root[groupName][itemName] = std::get<float>(item.value);
		}
		//Vector3型の値を所持していたら
		else if (std::holds_alternative<Vector3>(item.value)) {
			//float型のjson配列登録をする
			Vector3 value = std::get<Vector3>(item.value);
			root[groupName][itemName] = json::array({ value.x, value.y, value.z });
		}
		//ディレクトリのパス
		std::filesystem::path dir(kDirectoryPath);
		//ディレクトリがなければ作成する
		if (!std::filesystem::exists(dir)) {
			std::filesystem::create_directory(dir);
		}
		//書き込むjsonファイルのフルパスを合成する
		std::string filePath = kDirectoryPath + groupName + ".json";
		//書き込み用ファイルストリーム
		std::ofstream ofs;
		//ファイルを書き込み用に開く
		ofs.open(filePath);
		//ファイルオープン失敗の可能性あり
		if (ofs.fail()) {
			std::string message = "Failed open data file for write.";
			MessageBoxA(nullptr, message.c_str(), "GlobalVariables", 0);
			assert(0);
			return;
		}
		//ファイルにjson文字列を書き込む(インデント幅4)
		ofs << std::setw(4) << root << std::endl;
		//ファイルを閉じる
		ofs.close();
	}
}

void GlobalVariables::LoadFiles()
{
	//保存先ディレクトリのパスをローカル変数で宣言する
	std::filesystem::path dir(kDirectoryPath);
	//ディレクトリがなければスキップする
	if (!std::filesystem::exists(dir)) {
		return;
	}
	//ディレクトリのイテレーターを作る(多分フォルダを丸ごとイテレータ―にする感じ)
	std::filesystem::directory_iterator dir_it(kDirectoryPath);
	//イテレータ―からファイルをfor文でひとつずつ見ていく
	for (const std::filesystem::directory_entry& entry : dir_it) {
		//ファイルパスを取得
		const std::filesystem::path& filePath = entry.path();
		// extensionはファイルの拡張子のみを取得できる
		std::string extension = filePath.extension().string();
		// .json以外はスキップ
		if (extension.compare(".json") != 0) {
			// continueを使ってスキップする
			continue;
		}
		//ファイル読み込み関数
		// stemはファイルの拡張子を除いたファイル名のみを取得できる
		LoadFile(filePath.stem().string());
	}
}
void GlobalVariables::LoadFile(const std::string& groupName)
{
	//読み込むjsonファイルのフルパスを合成
	std::string filePath = kDirectoryPath + groupName + ".json";
	//読み込み用ファイルストリーム
	std::ifstream ifs;
	//ファイルを読み込み用に聞く
	ifs.open(filePath);
	//ファイルオープン失敗の可能性あり
	if (ifs.fail()) {
		std::string message = "Failed open data file for read.";
		MessageBoxA(nullptr, message.c_str(), "GlobalVariables", 0);
		assert(0);
	}
	json root;
	//json文字列をjsonのデータ構造に展開
	ifs >> root;
	//ファイルを閉じる
	ifs.close();
	//グループを検索
	json::iterator itGroup = root.find(groupName);
	//未登録チェック
	assert(itGroup != root.end());
	//各アイテムを探す
	for (json::iterator itItem = itGroup->begin(); itItem != itGroup->end(); ++itItem) {
		//アイテム名を取得
		const std::string& itemName = itItem.key();
		//アイテム名によって分岐する
		//int32_t型の値を所持していたら
		if (itItem->is_number_integer()) {
			//int型の値を登録
			int32_t value = itItem->get<int32_t>();
			SetValue(groupName, itemName, value);
		}
		//float型の値を所持していたら
		else if (itItem->is_number_float()) {
			//float型の値を登録
			double value = itItem->get<double>();
			//jsonオブジェクトはdouble型しかないので、キャストする
			SetValue(groupName, itemName,static_cast<float>(value));
		}
		//要素数3の配列であれば(つまりVector3)
		else if (itItem->is_array() && itItem->size() == 3) {
			//float型のjson配列登録
			Vector3 value = { itItem->at(0), itItem->at(1), itItem->at(2) };
			SetValue(groupName, itemName, value);
		}
	}

}


