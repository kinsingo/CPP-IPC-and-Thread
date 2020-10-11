#include <stdio.h>
#include <iostream> // cout, endl 사용하기 위해 사용
#include "1_classsample.h"

void main() {
	basic cls_basic(11); // 1 인스턴스 생성 // 4 초기화
	basic cls_basic2(12); // 2 인스턴스 생성 // 4 초기화

	cls_basic.printAge(); // 멤버함수 호출

	cls_basic.setAge(50); // 2 setter
	cls_basic.printAge(); // 멤버함수 호출

	cls_basic2.setAge(60); // 2 setter
	cls_basic2.printAge(); // 멤버함수 호출

	std::cout << basic::getInsCnt() << std::endl; // 3 getter
	std::cout << basic::getInsCnt() << std::endl; // 3 getter

	std::cout << cls_basic.n_day << std::endl; // 4 const 사용
	std::cout << cls_basic2.n_day << std::endl; // 4 const 사용

	std::cout << cls_basic.getDay() << std::endl; // 5 getter
	std::cout << cls_basic2.getDay() << std::endl; // 5 getter

	basic_friend cls_friend; // 6 friend 객체 생성
	std::cout << cls_basic.get_point_friend(cls_friend) << std::endl; // 6  friend 객체 private 접근 예제
	std::cout << cls_basic.init_point_friend(cls_friend) << std::endl; // 6 friend 객체 private 접근 예제

	// 7 상속 받은 자식 객체 생성
	basic_child cls_child;
	cls_child.print_parent(); // 부모 멤버 변수 접근
	cls_child.set_parent();   // 부모 멤버 변수 접근
	cls_child.print_parent(); // 부모 멤버 변수 접근
	
	// 8
	cls_child.print_overriding(); // 오버라이딩, 자식 내부에서 부모 멤버함수 호출
	cls_child.print_overload(1); // 오버로딩

	getchar(); // 엔터키 이후
	// cls_basic 소멸자 호출
	// cls_basic2 소멸자 호출
}	