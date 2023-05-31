
#ifndef TPERSON_H
#define TPERSON_H


#include <QObject>


class TPerson : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("author", "x")
    Q_CLASSINFO("version", "10.0.0")

    Q_PROPERTY(QString name MEMBER m_name)
    Q_PROPERTY(int score MEMBER m_score)
    Q_PROPERTY(int age READ age WRITE setAge NOTIFY ageChanged)
public:
  explicit TPerson(QString name, QObject *parent = nullptr);
  ~TPerson();
  int age();
  void setAge(int age);
  void incAge();
signals:
  void ageChanged(int age);
private:
  QString m_name;
  int m_age = 17;
  int m_score = 80;
};

#endif // TPERSON_H
