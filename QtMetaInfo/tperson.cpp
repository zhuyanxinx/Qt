
#include "tperson.h"

TPerson::TPerson(QString name, QObject* parent)
    : QObject { parent }
    , m_name { name }
{
}

TPerson::~TPerson()
{
    qDebug("Person cleal.");
}

int TPerson::age()
{
    return m_age;
}

void TPerson::setAge(int age)
{
    if (m_age != age) {
        m_age = age;
        emit ageChanged(m_age);
    }
}

void TPerson::incAge()
{
    ++m_age;
    emit ageChanged(m_age);
}
