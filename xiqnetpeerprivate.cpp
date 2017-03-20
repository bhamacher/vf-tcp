#include "xiqnetpeerprivate.h"

#include <QDataStream>
#include <QTcpSocket>

XiQNetPeerPrivate::XiQNetPeerPrivate(XiQNetPeer *t_publicPeer) :  q_ptr(t_publicPeer)
{
}

QByteArray XiQNetPeerPrivate::readArray() const
{
  Q_ASSERT(m_tcpSock != 0 && m_tcpSock->isOpen());

  QByteArray retVal;
  QDataStream in(m_tcpSock);
  in.setVersion(QDataStream::Qt_4_0);
  in.startTransaction();
  in >> retVal;

  if (in.commitTransaction() == true)
  {
    return retVal;
  }
  else //need to wait for more data
  {
    return QByteArray();
  }
}

void XiQNetPeerPrivate::sendArray(const QByteArray &t_byteArray) const
{
  Q_ASSERT(m_tcpSock != 0 && m_tcpSock->isOpen());

  QDataStream out(m_tcpSock);
  out.setVersion(QDataStream::Qt_4_0);
  out << t_byteArray;
}
