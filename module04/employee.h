#pragma once
#include <string>

using namespace std;

class employee {
public:
    enum gender_t {
        female, male
    };
    enum department_t {
        it, sales, finance, hr
    };
    employee(): m_first_name("jack"), m_last_name("bauer"),m_gender(male),
               m_salary(1'000'000),m_iban("tr1"),m_birth_year(1963),
               m_department(it){ }

    employee(const string &mFirstName, const string &mLastName, department_t mDepartment, gender_t mGender,
             double mSalary, const string &mIban, int mBirthYear) : m_first_name(mFirstName), m_last_name(mLastName),
                                                                    m_department(mDepartment), m_gender(mGender),
                                                                    m_salary(mSalary), m_iban(mIban),
                                                                    m_birth_year(mBirthYear) {}

    const string &getFirstName() const {
        return m_first_name;
    }

    const string &getLastName() const {
        return m_last_name;
    }

    department_t getDepartment() const {
        return m_department;
    }

    gender_t getGender() const {
        return m_gender;
    }

    double getSalary() const {
        return m_salary;
    }

    const string &getIban() const {
        return m_iban;
    }

    int getBirthYear() const {
        return m_birth_year;
    }

private:
    string m_first_name;
    string m_last_name;
    department_t m_department;
    gender_t m_gender;
    double m_salary;
    string m_iban;
    int m_birth_year;
};

