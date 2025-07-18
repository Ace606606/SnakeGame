// ./include/gameWidget.cpp
#include "game_widget.hpp"

#include <QDebug>
#include <QKeyEvent>
#include <QPainter>

GameWidget::GameWidget(QWidget* parent)
    : QWidget(parent), direction(1, 0), gridSize(20) {
    setFocusPolicy(Qt::StrongFocus);  // отлов клавиш
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameWidget::updateGame);
}

void GameWidget::setSpeed(int ms) { timer->setInterval(ms); }

void GameWidget::setWallCrossing(bool enabled) { allowWallCrossing = enabled; }

void GameWidget::startGame() {
    snake.clear();
    snake.append(QPoint(5, 5));
    snake.append(QPoint(4, 5));
    snake.append(QPoint(3, 5));
    direction = QPoint(1, 0);  // направо
    timer->start();
}

void GameWidget::paintEvent(QPaintEvent*) {
    // художник
    QPainter painter(this);
    painter.setBrush(Qt::green);
    for (const QPoint& part : snake) {
        painter.drawRect(part.x() * gridSize, part.y() * gridSize, gridSize,
                         gridSize);
    }
}

void GameWidget::updateGame() {
    QPoint head = snake.front() + direction;
    qDebug() << "updateGame called";
    // проверка границ
    if (head.x() < 0 || head.x() >= width() / gridSize || head.y() < 0 ||
        head.y() >= height() / gridSize) {
        timer->stop();
        qDebug() << "GameOver: столкновение со стеной";
        return;
    } else {
        // "Обход" границ — появление с противоположной стороны
        int maxX = width() / gridSize;
        int maxY = height() / gridSize;
        if (head.x() < 0) head.setX(maxX - 1);
        if (head.x() >= maxX) head.setX(0);
        if (head.y() < 0) head.setY(maxY - 1);
        if (head.y() >= maxY) head.setY(0);
    }

    snake.prepend(head);
    snake.removeLast();

    update();
}

void GameWidget::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) {
        case Qt::Key_Up:
        case Qt::Key_W:
            if (direction != QPoint(0, 1)) direction = QPoint(0, -1);
            break;
        case Qt::Key_Down:
        case Qt::Key_S:
            if (direction != QPoint(0, -1)) direction = QPoint(0, 1);
            break;
        case Qt::Key_Left:
        case Qt::Key_A:
            if (direction != QPoint(1, 0)) direction = QPoint(-1, 0);
            break;
        case Qt::Key_Right:
        case Qt::Key_D:
            if (direction != QPoint(-1, 0)) direction = QPoint(1, 0);
            break;
        default:
            break;
    }
}