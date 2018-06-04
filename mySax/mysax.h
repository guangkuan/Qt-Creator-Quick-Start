#ifndef MYSAX_H
#define MYSAX_H

#include <QXmlDefaultHandler>

class QListWidget;

class MySAX : public QXmlDefaultHandler
{
public:
    MySAX();
    ~MySAX();
    //readFile()函数用来读入XML文件
    bool readFile(const QString &fileName);

protected:
    bool startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts);
    bool endElement(const QString &namespaceURI, const QString &localName, const QString &qName);
    bool characters(const QString &ch);
    bool fatalError(const QXmlParseException &exception);

private:
    //QListWidget部件用来显示解析后的XML文档内容
    QListWidget *list;
    //currentText字符串变量用于暂存字符数据
    QString currentText;
};

#endif // MYSAX_H
