#include <iostream>
#include "util/delegate.h"
#include "comm/command.h"
#include "comm/command_params.h"
#include "comm/winboard_interface.h"

using namespace std;

WinBoard_Interface interface;

int main() {

	WinBoard_Command command("xboard");

	WinBoard_Command::CDelegate d1(
		[=](WinBoard_CommandParams const & p) -> void {
			cout << "Merge Bine!!" << endl;
			cout.flush();
		}
	);

	WinBoard_Command::CDelegate d2(
		[=](WinBoard_CommandParams const & p) -> void {
			cout << "Merge Super!!" << endl;
			cout.flush();
		}
	);

	interface.add(command);

	interface.get("xboard").add(d1);
	interface.get("xboard").add(d2);

	std::string scommand;
	cin >> scommand;

	interface.run(scommand);
	return 0;
}