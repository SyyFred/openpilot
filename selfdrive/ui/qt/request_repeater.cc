#include "request_repeater.hpp"

RequestRepeater::RequestRepeater(QObject *parent, QString requestURL, const QString &cacheKey,
                                 int period) : HttpRequest(parent, requestURL, cacheKey) {
  timer = new QTimer(this);
  timer->setTimerType(Qt::VeryCoarseTimer);
  QObject::connect(timer, &QTimer::timeout, [=](){
    if (!QUIState::ui_state.scene.started && QUIState::ui_state.awake && reply == NULL) {
      sendRequest(requestURL);
    }
  });
  timer->start(period * 1000);
}
