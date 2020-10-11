#include <stdio.h>
#include "1_classsample.h"

int basic::st_n_instance_cnt = 0;

basic::basic(int _n_day) : n_day(_n_day) { // 4  �ʱ�ȭ (������ ȣ��Ǹ鼭) 
	n_age = 40;
	st_n_instance_cnt++;
	printf("called new\n");
}

basic::~basic() {

}

void basic::printAge() {
	printf("%d\n", n_age);
}

void basic::setAge(int _n_age) { // 2 setter
	n_age = _n_age;
}


void basic::addInsCnt() { // 3 static �Լ� ������
	st_n_instance_cnt++;
}

int basic::getInsCnt() { // 3 static �Լ� ������
	return st_n_instance_cnt;
}


// 7 �θ�Ŭ���� ����
basic_parent::basic_parent() {
	n_parent_num_private = 100;
	n_parent_num_protected = 100;

	printf("parent new\n");
}
// 7 �θ�Ŭ���� �Ҹ���
basic_parent::~basic_parent() {
	printf("parent delete\n");
}

// 8 �θ�Ŭ���� �Լ� ����, ����
void basic_parent::print_overriding() {
	printf("print_overriding - parent\n");
}

// 7 �ڽ�Ŭ���� ������
basic_child::basic_child() {
	printf("child new\n");
}
// 7 �ڽ�Ŭ���� �Ҹ���
basic_child::~basic_child() {
	printf("child delete\n");
}
// 7 �ڽ�Ŭ���� 
void basic_child::set_parent() {
	n_parent_num_protected = 200; // protected ����
}
// 7
void basic_child::print_parent() {
	printf("print parent %d\n", n_parent_num_protected);
}

// 8  �θ�Ŭ���� �Լ��� �ڽ�Ŭ�������� ������, ����
void basic_child::print_overriding() {
	printf("print_overriding - child\n");
	basic_parent::print_overriding();
}
// 8 �����ε�
void basic_child::print_overload(int a) {
	printf("print_overriding 1\n");
}
// 8 �����ε�
void basic_child::print_overload(int a, int b) {
	printf("print_overriding 2\n");
}