#include "../../../include/Nuz.h"
#include <iostream>
using namespace std;
using namespace Nuz;

int main() {
	auto& e = IEngine::GetGameDevice();
	e.SetWindowTitle("Nuz zuN");
	e.InitWindow(800, 600, false);
	auto s = Nuz::IScene::CreateScene("HelloWorld");
	auto p = Nuz::IScene::GetScene("HelloWorld");
	e.GetSceneManager().Start(s);
	system("pause");

	return 0;
}