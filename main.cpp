#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

QT_USE_NAMESPACE

    class ChartWindow : public QMainWindow {
public:
    ChartWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        // Create a line series and add some points
        QLineSeries *series = new QLineSeries();
        series->append(0, 6);
        series->append(2, 4);
        series->append(3, 8);
        series->append(7, 4);
        series->append(10, 5);

        // Create a chart and add the line series
        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->createDefaultAxes();
        chart->setTitle("Simple Line Chart Example");

        // Create a chart view and set the chart
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        // Set the chart view as the central widget
        setCentralWidget(chartView);
        resize(800, 600);
    }
};

class WelcomeWindow : public QMainWindow {
public:
    WelcomeWindow() {
        // Create a central widget and layout
        QWidget *centralWidget = new QWidget(this);
        QVBoxLayout *layout = new QVBoxLayout(centralWidget);

        // Create and style the welcome label
        QLabel *welcomeLabel = new QLabel("Welcome to Chart Viewer", centralWidget);
        QFont labelFont = welcomeLabel->font();
        labelFont.setPointSize(24);
        welcomeLabel->setFont(labelFont);

        // Create the button
        QPushButton *showChartButton = new QPushButton("Show Chart", centralWidget);
        showChartButton->setMinimumSize(200, 50);
        QFont buttonFont = showChartButton->font();
        buttonFont.setPointSize(12);
        showChartButton->setFont(buttonFont);

        // Add widgets to layout
        layout->addStretch();
        layout->addWidget(welcomeLabel, 0, Qt::AlignCenter);
        layout->addSpacing(20);
        layout->addWidget(showChartButton, 0, Qt::AlignCenter);
        layout->addStretch();

        // Set up the central widget
        centralWidget->setLayout(layout);
        setCentralWidget(centralWidget);

        // Connect button click to opening chart window
        connect(showChartButton, &QPushButton::clicked, this, &WelcomeWindow::showChart);

        // Set window properties
        resize(400, 300);
        setWindowTitle("Welcome");
    }

private slots:
    void showChart() {
        ChartWindow *chartWindow = new ChartWindow();
        chartWindow->setAttribute(Qt::WA_DeleteOnClose);
        chartWindow->show();
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    WelcomeWindow welcomeWindow;
    welcomeWindow.show();

    return a.exec();
}
