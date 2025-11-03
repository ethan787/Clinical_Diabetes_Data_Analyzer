#include <QApplication>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QFormLayout>
#include <QLineEdit>
#include <QGroupBox>
#include <QComboBox>
#include <QSpinBox>
#include <QStackedWidget>

QT_USE_NAMESPACE

class ChartWindow : public QMainWindow
{
public:
    ChartWindow(QWidget *parent = nullptr)
        : QMainWindow(parent)
    {
        //make layout
        QWidget *chartWidget = new QWidget(this);
        QVBoxLayout *chartLayout = new QVBoxLayout();

        // Making a heading
        QLabel *heading = new QLabel("Wrong Page");
        QFont font = heading->font();
        font.setPointSize(24);
        heading->setStyleSheet("font-weight: bold;");

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

        // Create Button
        QPushButton *button = new QPushButton("Done", chartWidget);
        button->setMinimumSize(200, 50);
        QFont buttonFont = button->font();
        buttonFont.setPointSize(12);
        button->setFont(buttonFont);
        button->setStyleSheet("color : #767676; font-weight: bold;");

        // Setting up the layout & widget
        chartLayout->addWidget(heading, 0, Qt::AlignCenter);
        chartLayout->addWidget(chartView);
        chartLayout->addWidget(button, 0, Qt::AlignCenter);
        chartWidget->setLayout(chartLayout);
        setCentralWidget(chartWidget);
        resize(800, 600);
    }
};

class WelcomeWindow : public QMainWindow
{
public:
    WelcomeWindow()
    {
        //Widgets: StackedWidget -> Page1 Page2

        // Setup
        QWidget *centralWidget = new QWidget(this);
        cards = new QStackedWidget();
        QVBoxLayout *layout = new QVBoxLayout(centralWidget);


        //PAGE 1 !!!!!!!!
        QWidget *page1 = new QWidget;
        QVBoxLayout *layout1 = new QVBoxLayout(page1);

        // welcome label
        QLabel *welcomeLabel = new QLabel("Clinical Data Diabetic Analyzer", centralWidget);
        QFont labelFont = welcomeLabel->font();
        labelFont.setPointSize(24);
        welcomeLabel->setFont(labelFont);
        welcomeLabel->setStyleSheet("color : #767676; font-weight: bold;");

        // filter label
        QLabel *filterLabel = new QLabel("Filters:", centralWidget);
        labelFont.setPointSize(18);
        filterLabel->setFont(labelFont);
        filterLabel->setStyleSheet("QLabel {color : #B2B2B2}");

        // divider
        QFrame *divider = new QFrame();
        divider->setFrameShape(QFrame::HLine);
        divider->setFrameShadow(QFrame::Sunken);

        // form
        QGroupBox *form = new QGroupBox(tr(""));
        QFormLayout *layoutF = new QFormLayout;
        layoutF->addRow(new QLabel(tr("Age:")), new QSpinBox);
        layoutF->addRow(new QLabel(tr("Gender:")), new QComboBox);
        layoutF->addRow(new QLabel(tr("Type of Graph:")), new QComboBox);
        layoutF->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);

        QVBoxLayout *verticalBox = new QVBoxLayout;
        verticalBox->addStretch();
        verticalBox->addLayout(layoutF);
        verticalBox->addStretch();

        form->setLayout(verticalBox);
        form->setMinimumWidth(300);
        form->setMinimumHeight(200);

        // show chart button
        QPushButton *showChartButton = new QPushButton("Show Chart", centralWidget);
        showChartButton->setMinimumSize(200, 50);
        QFont buttonFont = showChartButton->font();
        buttonFont.setPointSize(12);
        showChartButton->setFont(buttonFont);
        showChartButton->setStyleSheet("color : #767676; font-weight: bold;");

        // page 1 layout
        layout1->addStretch(0);
        layout1->addWidget(welcomeLabel, 0, Qt::AlignCenter);
        layout1->addSpacing(30);
        layout1->addWidget(filterLabel, 0, Qt::AlignCenter);
        layout1->addSpacing(10);
        layout1->addWidget(divider);
        layout1->addSpacing(10);
        layout1->addWidget(form, 0, Qt::AlignCenter);
        layout1->addSpacing(30);
        layout1->addWidget(showChartButton, 0, Qt::AlignCenter);
        layout1->addStretch();


        // PAGE 2 !!!!!!
        // Setup
        QWidget *page2 = new QWidget;
        QVBoxLayout *layout2 = new QVBoxLayout(page2);

        // heading
        QLabel *heading = new QLabel("Graphs Based on Data Selected");
        QFont font = heading->font();
        font.setPointSize(24);
        heading->setStyleSheet("font-weight: bold;");

        // line series
        QLineSeries *series = new QLineSeries();
        series->append(0, 6);
        series->append(2, 4);
        series->append(3, 8);
        series->append(7, 4);
        series->append(10, 5);

        // chart
        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->createDefaultAxes();
        chart->setTitle("Line Chart");

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        // show page 3 button
        QPushButton *button = new QPushButton("Done", page2);
        button->setMinimumSize(200, 50);
        buttonFont = button->font();
        buttonFont.setPointSize(12);
        button->setFont(buttonFont);
        button->setStyleSheet("color : #767676; font-weight: bold;");

        // page 2 layout
        layout2->addWidget(heading, 0, Qt::AlignCenter);
        layout2->addWidget(chartView);
        layout2->addWidget(button, 0, Qt::AlignCenter);
        page2->setLayout(layout2);
        resize(800, 600);


        // PAGE 3 !!!!!
        QWidget *page3 = new QWidget;
        QVBoxLayout *layout3 = new QVBoxLayout();

        //heading
        QLabel *helpHeading = new QLabel("How to Get Help:");
        QFont helpFont = helpHeading->font();
        helpFont.setPointSize(24);
        helpHeading->setFont(helpFont);
        helpHeading->setStyleSheet("font-weight: bold;");

        //page 3 layout
        layout3->addWidget(helpHeading, 0, Qt::AlignCenter);
        page3->setLayout(layout3);



        // LAYOUT STUFF
        cards->addWidget(page1);
        cards->addWidget(page2);
        cards->addWidget(page3);

        // CONNECT STUFF
        connect(showChartButton, &QPushButton::clicked, this, [this]() {
            showChart();
        });
        connect(button, &QPushButton::clicked, this, [this]() {
            showPage();
        });

        layout->addWidget(cards);

        // Set up the central widget
        centralWidget->setLayout(layout);
        setCentralWidget(centralWidget);

        // Connect button click to opening chart window
        // connect(showChartButton, &QPushButton::clicked, this, &WelcomeWindow::showChart);

        // Set window properties
        resize(550, 600);
        setWindowTitle("Welcome");
    }

private:
    QStackedWidget *cards;
    void showChart()
    {
        cards->setCurrentIndex(1);
    }
    void showPage() {
        cards->setCurrentIndex(2);
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    WelcomeWindow welcomeWindow;
    welcomeWindow.show();

    return a.exec();
}
