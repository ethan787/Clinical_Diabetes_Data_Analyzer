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
        QLabel *heading = new QLabel("Graphs Based on Data Selected");
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

        // Setting up the layout & widget
        chartLayout->addWidget(heading, 0, Qt::AlignCenter);
        chartLayout->addWidget(chartView);
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
        // Create central widget and layout
        QWidget *centralWidget = new QWidget(this);
        QVBoxLayout *layout = new QVBoxLayout(centralWidget);

        // Create Welcome Label
        QLabel *welcomeLabel = new QLabel("Clinical Data Diabetic Analyzer", centralWidget);
        QFont labelFont = welcomeLabel->font();
        labelFont.setPointSize(24);
        welcomeLabel->setFont(labelFont);
        welcomeLabel->setStyleSheet("color : #767676; font-weight: bold;");

        // Create Filter Label
        QLabel *filterLabel = new QLabel("Filters:", centralWidget);
        labelFont.setPointSize(18);
        filterLabel->setFont(labelFont);
        filterLabel->setStyleSheet("QLabel {color : #B2B2B2}");

        // Create divider
        QFrame *divider = new QFrame();
        divider->setFrameShape(QFrame::HLine);
        divider->setFrameShadow(QFrame::Sunken);

        // Create Form
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

        // Create Button
        QPushButton *showChartButton = new QPushButton("Show Chart", centralWidget);
        showChartButton->setMinimumSize(200, 50);
        QFont buttonFont = showChartButton->font();
        buttonFont.setPointSize(12);
        showChartButton->setFont(buttonFont);
        showChartButton->setStyleSheet("color : #767676; font-weight: bold;");

        // Add widgets to layout
        layout->addStretch(0);
        layout->addWidget(welcomeLabel, 0, Qt::AlignCenter);
        layout->addSpacing(30);
        layout->addWidget(filterLabel, 0, Qt::AlignCenter);
        layout->addSpacing(10);
        layout->addWidget(divider);
        layout->addSpacing(10);
        layout->addWidget(form, 0, Qt::AlignCenter);
        layout->addSpacing(30);
        layout->addWidget(showChartButton, 0, Qt::AlignCenter);
        layout->addStretch();

        // Set up the central widget
        centralWidget->setLayout(layout);
        setCentralWidget(centralWidget);

        // Connect button click to opening chart window
        connect(showChartButton, &QPushButton::clicked, this, &WelcomeWindow::showChart);

        // Set window properties
        resize(550, 600);
        setWindowTitle("Welcome");
    }

private slots:
    void showChart()
    {
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
