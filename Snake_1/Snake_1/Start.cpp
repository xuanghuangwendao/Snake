#pragma once

#include "game_ui.h"
int main() {
	bool need_init = true;
	while (1) {
		//��ʼ����
		if (need_init) {
			if (!game_begin()) {
				continue;
			}
		}
		//��Ϸ����
		game_run();
		//��������
		int p = game_end();
		if (p == 1) {
			continue;
		}
		else if (p == 2) {
			need_init = false;
			continue;
		}
		else if (p == 3) {
			break;
		}

	}
	return 0;
	
}