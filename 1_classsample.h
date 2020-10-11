#pragma once
class basic_friend // 6
{
public:
	basic_friend() { n_my_point = 10000; }

	friend class basic;

private:
	int  n_my_point; // private ����
};

class basic
{
public:
	basic(int _n_day);
	~basic();

public:
	void printAge();

public: // 2 ����������
	void setAge(int _n_age); // 2 setter
	int getAge() { return n_age; }; // 2 getter

public: // 3
	static void addInsCnt(); // 3 static �Լ�
	static int getInsCnt(); // 3 static �ϸ���

	const int n_day; // 4 const

	int getDay() const { return n_day; }; // 5 const �Լ�

	int get_point_friend(basic_friend& _p_cls) { return _p_cls.n_my_point; }; // 6 friend
	int init_point_friend(basic_friend& _p_cls) { _p_cls.n_my_point = 0; return _p_cls.n_my_point; }; // 6

private:
	int  n_age;
	static int st_n_instance_cnt;
};

//7 �θ�Ŭ���� ����
class basic_parent
{
public:
	basic_parent();
	~basic_parent();

private:
	int n_parent_num_private;

protected:
	int n_parent_num_protected;

	void print_overriding(); // 8 �θ��Լ�
};

class basic_child :public basic_parent // ���
{
public:
	basic_child();
	~basic_child();

	void set_parent();
	void print_parent();

	void print_overriding(); // 8 �θ��Լ��� ������
	void print_overload(int a); // 8 �����ε�
	void print_overload(int a, int b); // 8 �����ε�
};