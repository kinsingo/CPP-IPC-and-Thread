#include <stdio.h>
#include <iostream> // cout, endl ����ϱ� ���� ���
#include "1_classsample.h"

void main() {
	basic cls_basic(11); // 1 �ν��Ͻ� ���� // 4 �ʱ�ȭ
	basic cls_basic2(12); // 2 �ν��Ͻ� ���� // 4 �ʱ�ȭ

	cls_basic.printAge(); // ����Լ� ȣ��

	cls_basic.setAge(50); // 2 setter
	cls_basic.printAge(); // ����Լ� ȣ��

	cls_basic2.setAge(60); // 2 setter
	cls_basic2.printAge(); // ����Լ� ȣ��

	std::cout << basic::getInsCnt() << std::endl; // 3 getter
	std::cout << basic::getInsCnt() << std::endl; // 3 getter

	std::cout << cls_basic.n_day << std::endl; // 4 const ���
	std::cout << cls_basic2.n_day << std::endl; // 4 const ���

	std::cout << cls_basic.getDay() << std::endl; // 5 getter
	std::cout << cls_basic2.getDay() << std::endl; // 5 getter

	basic_friend cls_friend; // 6 friend ��ü ����
	std::cout << cls_basic.get_point_friend(cls_friend) << std::endl; // 6  friend ��ü private ���� ����
	std::cout << cls_basic.init_point_friend(cls_friend) << std::endl; // 6 friend ��ü private ���� ����

	// 7 ��� ���� �ڽ� ��ü ����
	basic_child cls_child;
	cls_child.print_parent(); // �θ� ��� ���� ����
	cls_child.set_parent();   // �θ� ��� ���� ����
	cls_child.print_parent(); // �θ� ��� ���� ����
	
	// 8
	cls_child.print_overriding(); // �������̵�, �ڽ� ���ο��� �θ� ����Լ� ȣ��
	cls_child.print_overload(1); // �����ε�

	getchar(); // ����Ű ����
	// cls_basic �Ҹ��� ȣ��
	// cls_basic2 �Ҹ��� ȣ��
}	