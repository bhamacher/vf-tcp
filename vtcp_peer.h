#ifndef VEIN_TCP_PEER_H
#define VEIN_TCP_PEER_H

#include "vtcp_global.h"

#include <QObject>
#include <QString>
#include <QAbstractSocket>

QT_BEGIN_NAMESPACE
class QTcpSocket;
QT_END_NAMESPACE

namespace VeinTcp
{
  class TcpPeerPrivate;


  /**
 * @brief Custom QTcpSocket based implementation of a TCP network peer
 */
  class VEIN_TCPSHARED_EXPORT TcpPeer : public QObject
  {
    Q_OBJECT
  public:
    explicit TcpPeer(QObject *t_parent = 0);
    explicit TcpPeer(qintptr t_socketDescriptor, QObject *t_parent = 0);

    ~TcpPeer();

    QString getIpAddress() const;
    quint16 getPort() const;
    bool isConnected() const;


    QUuid getPeerId() const;
    void setPeerId(QUuid t_peerId);

    /**
   * @brief Allows access to the QTcpSocket
   * @return QTcpSocket used by this instance
   * @todo refactor, as this violates the OOP principle "separation of concerns"
   */
    QTcpSocket *getTcpSocket() const;

    QString getErrorString() const;

  signals:
    /**
   * @brief Emitted if successful connected
   */
    void sigConnectionEstablished(TcpPeer *t_sender);
    /**
   * @brief Emitted when the connection is interrupted
   */
    void sigConnectionClosed(TcpPeer *t_client);
    /**
   * @brief Emitted when incoming messages arrive
   * @param t_message
   * @bug Do not use the t_message parameter with Qt::QueuedConnection as it may be deleted before the slot is called
   */
    void sigMessageReceived(TcpPeer *t_sender, QByteArray t_message);
    /**
   * @brief Emitted on socket failure
   * @param t_socketError
   */
    void sigSocketError(QAbstractSocket::SocketError t_socketError);

  public slots:
    /**
   * @brief Transmits the message
   * @param t_message
   */
    void sendMessage(QByteArray t_message) const;
    /**
   * @brief Starts the connection in case of a dedicated host connection
   *
   * Called after Signal/Slot setup
   * @param t_ipAddress
   * @param t_port
   */
    void startConnection(QString t_ipAddress, quint16 t_port);
    /**
   * @brief Closes the connection
   */
    void stopConnection();

  protected slots:
    void onReadyRead();

  private:
    /**
   * @brief PIMPL pointer
   */
    TcpPeerPrivate *d_ptr = 0;
  };
}

#endif // VEIN_TCP_PEER_H
