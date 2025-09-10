#pragma once
#include <QString>

class Suburb {
public:
    Suburb() {}  // default

    Suburb(const QString &suburb,
           const QString &branchCode,
           const QString &region,
           const QString &speedDial,
           const QString &phone1,
           const QString &phone2,
           const QString &fax,
           const QString &email,
           const QString &manager,
           const QString &managerPhone,
           const QString &supervisor,
           const QString &supervisorPhone,
           const QString &supervisor2,
           const QString &supervisor2Phone,
           const QString &daysHomeVisit,
           const QString &hoursOpen,
           const QString &saturdayHoursOpen,
           const QString &dom1,
           const QString &dom2,
           const QString &dom3,
           const QString &dom4)
        : suburb(suburb), branchCode(branchCode), region(region), speedDial(speedDial),
        phone1(phone1), phone2(phone2), fax(fax), email(email), manager(manager),
        managerPhone(managerPhone), supervisor(supervisor), supervisorPhone(supervisorPhone),
        supervisor2(supervisor2), supervisor2Phone(supervisor2Phone), daysHomeVisit(daysHomeVisit),
        hoursOpen(hoursOpen), saturdayHoursOpen(saturdayHoursOpen), dom1(dom1), dom2(dom2),
        dom3(dom3), dom4(dom4) {}

    QString suburb, branchCode, region, speedDial;
    QString phone1, phone2, fax, email;
    QString manager, managerPhone, supervisor, supervisorPhone;
    QString supervisor2, supervisor2Phone;
    QString daysHomeVisit, hoursOpen, saturdayHoursOpen;
    QString dom1, dom2, dom3, dom4;
};

