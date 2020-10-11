#include <stdio.h>
#include "1_classsample.h"

int basic::st_n_instance_cnt = 0;

basic::basic(int _n_day) : n_day(_n_day) { // 4  초기화 (생성자 호출되면서) 
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


void basic::addInsCnt() { // 3 static 함수 구현부
	st_n_instance_cnt++;
}

int basic::getInsCnt() { // 3 static 함수 구현부
	return st_n_instance_cnt;
}


// 7 부모클래스 구현
basic_parent::basic_parent() {
	n_parent_num_private = 100;
	n_parent_num_protected = 100;

	printf("parent new\n");
}
// 7 부모클래스 소멸자
basic_parent::~basic_parent() {
	printf("parent delete\n");
}

// 8 부모클래스 함수 정의, 구현
void basic_parent::print_overriding() {
	printf("print_overriding - parent\n");
}

// 7 자식클래스 생성자
basic_child::basic_child() {
	printf("child new\n");
}
// 7 자식클래스 소멸자
basic_child::~basic_child() {
	printf("child delete\n");
}
// 7 자식클래스 
void basic_child::set_parent() {
	n_parent_num_protected = 200; // protected 예시
}
// 7
void basic_child::print_parent() {
	printf("print parent %d\n", n_parent_num_protected);
}

// 8  부모클래스 함수를 자식클래스에서 재정의, 구현
void basic_child::print_overriding() {
	printf("print_overriding - child\n");
	basic_parent::print_overriding();
}
// 8 오버로딩
void basic_child::print_overload(int a) {
	printf("print_overriding 1\n");
}
// 8 오버로딩
void basic_child::print_overload(int a, int b) {
	printf("print_overriding 2\n");
}