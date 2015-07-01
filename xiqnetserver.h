#ifndef H2012_xiqnet_SERVER_PUB_H
#define H2012_xiqnet_SERVER_PUB_H

#include "xiqnet_global.h"

#include <QTcpServer>

#include <QList>

class XiQNetServerPrivate;
class XiQNetPeer;
class XiQNetWrapper;
namespace google
{
  namespace protobuf
  {
    class Message;
  }
}

class XIQNET_QTSHARED_EXPORT XiQNetServer : public QTcpServer
{
  Q_OBJECT
public:
  explicit XiQNetServer(QObject *t_parent = 0);
  virtual ~XiQNetServer();

  QList<XiQNetPeer*> getClientList() const;

  /**
   * @brief Incoming connections use the default XiQNetWrapper for messaging
   * @param wrapper
   */
  void setDefaultWrapper(XiQNetWrapper *t_wrapper);

signals:
  /**
   * @brief A new client connected
   * @param newClient
   */
  void sigClientConnected(XiQNetPeer *t_peer);

public slots:
  /**
   * @brief Sends the message to all peers of this server
   * @param pMessage
   */
  void broadcastMessage(google::protobuf::Message *t_message) const;

  /**
   * @brief Convenient function for QTcpServer::listen()
   * @note Prints out the server port to the debug message handler
   * @param uPort
   */
  void startServer(quint16 t_port);

protected slots:
  /**
   * @brief For reference housekeeping
   */
  void clientDisconnectedSRV();

protected:
  /**
   * @brief Override of QTcpServer function
   * @param sockDesc
   */
  void incomingConnection(qintptr t_socketDescriptor) override;

private:
  /**
   * @brief PIMPL pointer
   */
  XiQNetServerPrivate *d_ptr = 0;

  Q_DISABLE_COPY(XiQNetServer)
  Q_DECLARE_PRIVATE(XiQNetServer)
};

#endif // H2012_xiqnet_SERVER_H
