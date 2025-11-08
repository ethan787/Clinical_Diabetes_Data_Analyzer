#include <QApplication>
#include <QMainWindow>
#include <QStackedWidget>
#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QComboBox>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QLineEdit>
#include <QMessageBox>
#include <iostream>
#include <map>
#include "data_set.h"
#include "CSV.h"
#include "filters.h"
#include "sort.h"
#include "stats.h"
#include <QDir>


using namespace std;

QT_USE_NAMESPACE


    class WelcomeWindow : public QMainWindow
{
public:
    WelcomeWindow()
    {
        // Setup
        QWidget *centralWidget = new QWidget(this);
        cards = new QStackedWidget();
        QVBoxLayout *layout = new QVBoxLayout(centralWidget);


        //PAGE 1 !!!!!!!!
        QWidget *page1 = new QWidget;
        QVBoxLayout *layout1 = new QVBoxLayout(page1);

        // welcome label
        QLabel *welcomeLabel = new QLabel("Clinical Data Diabetic Analyzer", centralWidget);
        QFont headingFont = welcomeLabel->font();
        headingFont.setPointSize(24);
        welcomeLabel->setFont(headingFont);
        welcomeLabel->setStyleSheet("color: rgb(140, 180, 220); font-weight: bold;");

        // filter label
        QLabel *filterLabel = new QLabel("Filters:", centralWidget);
        QFont sHeadingFont = filterLabel->font();
        sHeadingFont.setPointSize(18);
        filterLabel->setFont(sHeadingFont);
        filterLabel->setStyleSheet("color: rgb(180, 203, 236);");

        // divider
        QFrame *divider = new QFrame();
        divider->setFrameShape(QFrame::HLine);
        divider->setFrameShadow(QFrame::Sunken);
        divider->setStyleSheet("background-color: rgb(160, 200, 240);");

        // form
        QGroupBox *form = new QGroupBox(tr(""));
        QFormLayout *layoutF = new QFormLayout;

        minAgeBox = new QSpinBox();
        minAgeBox->setRange(0, 110);
        minAgeBox->setValue(0);

        maxAgeBox = new QSpinBox();
        maxAgeBox->setRange(0, 110);
        maxAgeBox->setValue(110);

        genderBox = new QComboBox;
        genderBox->addItem("All");
        genderBox->addItem("Male");
        genderBox->addItem("Female");
        genderBox->addItem("Other");

        chartBox = new QComboBox;
        chartBox->addItem("Line Chart (Glucose)");
        chartBox->addItem("Bar Chart (Age Distribution)");
        chartBox->addItem("Pie Chart (Diabetes %)");

        algoBox = new QComboBox;
        algoBox->addItem("Quick Sort");
        algoBox->addItem("Merge Sort");

        fieldBox = new QComboBox;
        fieldBox->addItem("Age");
        fieldBox->addItem("Glucose");
        fieldBox->addItem("HbA1c");
        fieldBox->addItem("BMI");

        layoutF->addRow(new QLabel(tr("Min Age:")), minAgeBox);
        layoutF->addRow(new QLabel(tr("Max Age:")), maxAgeBox);
        layoutF->addRow(new QLabel(tr("Gender:")), genderBox);
        layoutF->addRow(new QLabel(tr("Type of Graph:")), chartBox);
        layoutF->addRow(new QLabel(tr("Sort Algorithm:")), algoBox);
        layoutF->addRow(new QLabel(tr("Sort By:")), fieldBox);

        layoutF->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        form->setStyleSheet("QWidget {color: rgb(140, 180, 220);} QGroupBox {border: 2px solid rgb(160, 200, 240); border-radius: 5px; width: 400px; background-color: white;}");
        minAgeBox->setStyleSheet("background-color: rgb(232, 242, 251); color: rgb(140, 180, 220);");
        maxAgeBox->setStyleSheet("background-color: rgb(232, 242, 251); color: rgb(140, 180, 220);");
        genderBox->setStyleSheet("background-color: rgb(232, 242, 251); color: rgb(140, 180, 220);");
        chartBox->setStyleSheet("background-color: rgb(232, 242, 251); color: rgb(140, 180, 220);");
        genderBox->setStyleSheet("background-color: rgb(232, 242, 251); color: rgb(140, 180, 220);");
        algoBox->setStyleSheet("background-color: rgb(232, 242, 251); color: rgb(140, 180, 220);");
        fieldBox->setStyleSheet("background-color: rgb(232, 242, 251); color: rgb(140, 180, 220);");
        // fieldBox->setHidden(true);

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
        showChartButton->setStyleSheet("QPushButton {background-color: white; color : rgb(160, 200, 240); font-weight: bold;} QPushButton:hover {background-color: rgb(245, 250, 255);} QPushButton:pressed {background-color: rgb(200, 220, 240);}");

        // page 1 layout
        layout1->addStretch(0);
        layout1->addWidget(welcomeLabel, 0, Qt::AlignCenter);
        layout1->addSpacing(10);
        layout1->addWidget(divider);
        layout1->addSpacing(30);
        layout1->addWidget(filterLabel, 0, Qt::AlignCenter);        
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
        QLabel *heading = new QLabel("Graph Based on Data Selected");
        heading->setFont(headingFont);
        heading->setStyleSheet("color : rgb(180, 203, 236); font-weight: bold;");

        // show back button
        QPushButton *backButton = new QPushButton("Back", page2);
        backButton->setMinimumSize(200, 50);
        backButton->setFont(buttonFont);
        backButton->setStyleSheet("QPushButton {background-color: white; color : rgb(160, 200, 240); font-weight: bold;} QPushButton:hover {background-color: rgb(245, 250, 255);} QPushButton:pressed {background-color: rgb(200, 220, 240);}");

        // show page 3 button
        QPushButton *doneButton = new QPushButton("Done", page2);
        doneButton->setMinimumSize(200, 50);
        doneButton->setFont(buttonFont);
        doneButton->setStyleSheet("QPushButton {background-color: white; color : rgb(160, 200, 240); font-weight: bold;} QPushButton:hover {background-color: rgb(245, 250, 255);} QPushButton:pressed {background-color: rgb(200, 220, 240);}");

        QHBoxLayout *buttonBox = new QHBoxLayout;
        buttonBox->addWidget(backButton);
        buttonBox->addWidget(doneButton);

        // page 2 layout
        layout2->addWidget(heading, 0, Qt::AlignCenter);
        layout2->addStretch();
        layout2->addLayout(buttonBox);
        layout2->addSpacing(10);
        page2->setLayout(layout2);
        resize(800, 600);


        // PAGE 3 !!!!!
        QWidget *page3 = new QWidget;
        QVBoxLayout *layout3 = new QVBoxLayout();

        QPushButton *homeButton = new QPushButton("Home", page3);
        homeButton->setMinimumSize(60, 35);
        homeButton->setFont(buttonFont);
        homeButton->setStyleSheet("QPushButton {background-color: white; color : rgb(160, 200, 240); font-weight: bold;} QPushButton:hover {background-color: rgb(245, 250, 255);} QPushButton:pressed {background-color: rgb(200, 220, 240);}");

        //heading
        QLabel *helpHeading = new QLabel("How to Get Help:");
        helpHeading->setFont(headingFont);
        helpHeading->setStyleSheet("color: rgb(140, 180, 220); font-weight: bold;");

        QLabel *linksSHeading = new QLabel("Links:");
        linksSHeading->setFont(sHeadingFont);        
        linksSHeading->setStyleSheet("color: rgb(180, 203, 236); font-weight: bold; font-size: 16px;");

        QLabel *link1 = new QLabel("<a style='color: rgb(160, 160, 220);' href = \"https://www.redcross.org/about-us/news-and-events/news/2025/diabetes-month--busting-myths--saving-lives.html?srsltid=AfmBOoqMTT_ojPT9rooqXcW0F9jhzdG5rQ9TrjiAL6D3zQuWBrg4rpm7\">Red Cross: Diabetes Myths</a>");
        link1->setTextInteractionFlags(Qt::TextBrowserInteraction);
        link1->setOpenExternalLinks(true);

        QLabel *link2 = new QLabel("<a style='color: rgb(160, 160, 220);' href = \"https://www.mayoclinic.org/diseases-conditions/type-2-diabetes/in-depth/diabetes-prevention/art-20047639\">Mayo Clinic: Diabetes Prevention</a>");
        link2->setTextInteractionFlags(Qt::TextBrowserInteraction);
        link2->setOpenExternalLinks(true);

        QLabel *link3 = new QLabel("<a style='color: rgb(160, 160, 220);' href = \"https://www.niddk.nih.gov/health-information/diabetes/overview/insulin-medicines-treatments\">NIH: Diabetes Treatment</a>");
        link3->setTextInteractionFlags(Qt::TextBrowserInteraction);
        link3->setOpenExternalLinks(true);

        QHBoxLayout *linkBox = new QHBoxLayout;
        linkBox->addWidget(link1, 0, Qt::AlignCenter);
        linkBox->addWidget(link2, 0, Qt::AlignCenter);
        linkBox->addWidget(link3, 0, Qt::AlignCenter);

        QLabel *prevSHeading = new QLabel("Steps to Prevention:");
        prevSHeading->setFont(sHeadingFont);
        prevSHeading->setStyleSheet("color: rgb(180, 203, 236); font-weight: bold;");

        QFrame *paragraph = new QFrame;
        paragraph->setFrameShape(QFrame::Box);
        paragraph->setFrameShadow(QFrame::Plain);
        paragraph->setLineWidth(1);
        paragraph->setStyleSheet("background-color: rgb(250, 254, 255); border-radius: 15px; padding: 10px; font-size: 16px; color: rgb(100, 130, 200);");

        QVBoxLayout *paragraphLayout = new QVBoxLayout(paragraph);

        QLabel *prevParagraph = new QLabel(
            "Managing diabetes is about awareness and lifestyle choices. "
            "<br><b>1. Healthy Eating:</b> Focus on whole grains, lean proteins, fruits, and vegetables. "
            "<br><b>2. Physical Activity:</b> Aim for at least 30 minutes of moderate exercise most days of the week. "
            "<br><b>3. Monitor Blood Sugar:</b> Regularly check your glucose levels as advised by your doctor. "
            "<br><b>4. Regular Check-ups:</b> Visit your healthcare provider for regular check-ups to monitor for complications. "
            "<br><br>Prevention is important because uncontrolled diabetes can lead to serious health issues, including heart disease, kidney damage, and vision problems. "
            "Early detection and management can significantly improve long-term health outcomes."
            "<br>"
            );
        prevParagraph->setWordWrap(true);
        prevParagraph->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        paragraph->setLayout(paragraphLayout);
        paragraph->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        paragraphLayout->addWidget(prevParagraph);

        //page 3 layout
        layout3->addStretch();
        layout3->addWidget(homeButton, 0, Qt::AlignLeft);
        layout3->addWidget(helpHeading, 0, Qt::AlignCenter);
        layout3->addSpacing(10);
        layout3->addWidget(divider);
        layout3->addSpacing(10);
        layout3->addWidget(prevSHeading, 0, Qt::AlignCenter);
        layout3->addSpacing(10);
        layout3->addStretch();
        layout3->addWidget(paragraph, 0, Qt::AlignCenter);
        layout3->addStretch();
        layout3->addSpacing(5);
        layout3->addWidget(linksSHeading, 0, Qt::AlignCenter);
        layout3->addSpacing(10);
        layout3->addLayout(linkBox);
        layout3->addStretch();
        page3->setLayout(layout3);



        // LAYOUT STUFF
        cards->addWidget(page1);
        cards->addWidget(page2);
        cards->addWidget(page3);

        // CONNECT STUFF
        connect(showChartButton, &QPushButton::clicked, this, &WelcomeWindow::runBackendPipeline);
        connect(backButton, &QPushButton::clicked, this, &WelcomeWindow::showPageOne);
        connect(doneButton, &QPushButton::clicked, this, &WelcomeWindow::showHelpPage);
        connect(homeButton, &QPushButton::clicked, this, &WelcomeWindow::showPageOne);
        connect(chartBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=](int index) {
            if (index == 0) {
                // fieldBox->setHidden(false);
                layoutF->labelForField(fieldBox)->show();
                fieldBox->show();
            } else {
                // fieldBox->setHidden(true);
                layoutF->labelForField(fieldBox)->hide();
                fieldBox->hide();
            }
        });

        layout->addWidget(cards);

        // Set up the central widget
        centralWidget->setLayout(layout);
        setCentralWidget(centralWidget);

        // load of CSV data when the app starts
        loadData();

        // Set window properties
        QPalette palette;
        palette.setColor(QPalette::Window, QColor(232, 242, 251));
        setAutoFillBackground(true);
        resize(550, 600);
        setPalette(palette);
        setWindowTitle("Diabetic Analyzer");
    }


private:
    QStackedWidget *cards;
    QComboBox *chartBox;
    QComboBox *genderBox;
    QSpinBox *minAgeBox;
    QSpinBox *maxAgeBox;
    QComboBox *algoBox;
    QComboBox *fieldBox;
    std::vector<DataRecord> allPatientData;

    void loadData() {
        QString baseDir = QCoreApplication::applicationDirPath();
        QDir projectDir(baseDir);
        if (projectDir.cdUp()) {
            projectDir.cd("DSAProj2");
        }

        QString filePath = projectDir.filePath("diabetes_dataset_with_notes.csv");

        std::string filename = filePath.toStdString();
        allPatientData = load_CSV(filename);

        if (allPatientData.empty()) {
            QMessageBox::critical(
                this, "Error",
                QString("Failed to load data from '%1'.\n\nLooked in:\n%2")
                    .arg(QString::fromStdString(filename))
                    .arg(filePath)
                );
        } else {
            std::cout << "Successfully loaded " << allPatientData.size()
                << " records from " << filename << std::endl;
        }
    }

    void runBackendPipeline() {
        QElapsedTimer timer;
        timer.start();
        // 1. Get all values from the UI
        QString chartType = chartBox->currentText();
        QString gender = genderBox->currentText();
        int minAge = minAgeBox->value();
        int maxAge = maxAgeBox->value();

        Algorithm algo = (algoBox->currentText() == "Quick Sort") ? Algorithm::Quick : Algorithm::Merge;

        SortField field;
        QString fieldText = fieldBox->currentText();
        if (fieldText == "Age") field = SortField::Age;
        else if (fieldText == "Glucose") field = SortField::Glucose;
        else if (fieldText == "HbA1c") field = SortField::HbA1c;
        else field = SortField::BMI;

        // 2. Run Filter.cpp Pipeline
        std::cout << "Filtering " << allPatientData.size() << " records..." << std::endl;
        std::vector<DataRecord> filteredData = allPatientData;

        if (gender != "All") {
            filteredData =filterGen(filteredData, gender.toStdString());
        }
        filteredData = filterAge(filteredData, minAge, maxAge);
        std::cout << "Found " << filteredData.size() << " matching records." << std::endl;

        if (filteredData.empty()) {
            QMessageBox::warning(this, "No Data", "No data matched your filter criteria.");
            return;
        }

        // 3. Run Sort Methods
        std::cout << "Sorting data with " << algoBox->currentText().toStdString() << "..." << std::endl;
        sort_records(filteredData, algo, field, SortOrder::Asc);
        std::cout << "Sort complete." << std::endl;
        cout << algoBox->currentText().toStdString() << " took " << timer.elapsed() << " ms to run." << endl;

        // 4. Get Stats & Show Chart
        cards->setCurrentIndex(1);
        QWidget *page2 = cards->widget(1);
        QVBoxLayout *layout2 = qobject_cast<QVBoxLayout*>(page2->layout());

        clearOldChart(layout2);

        if (chartType.startsWith("Line Chart")) {
            showLineChart(layout2, filteredData);
        } else if (chartType.startsWith("Pie Chart")) {
            showPieChart(layout2, filteredData);
        } else if (chartType.startsWith("Bar Chart")) {
            showBarChart(layout2, filteredData);
        }
    }

    void clearOldChart(QVBoxLayout* layout) {
        if (layout->count() > 2) {
            QLayoutItem* item = layout->itemAt(1);
            if (item && item->widget()) {
                if (dynamic_cast<QChartView*>(item->widget())) {
                    layout->removeItem(item);
                    delete item->widget();
                    delete item;
                }
            }
        }
    }

    void showPageOne() {
        cards->setCurrentIndex(0);
    }

    void showHelpPage() {
        cards->setCurrentIndex(2);
    }
    void showLineChart(QVBoxLayout* layout, const std::vector<DataRecord>& data) {
        QLineSeries *series = new QLineSeries();

        int count = 0;
        for (const auto& record : data) {
            if (record.has_glucose == true) {
                series->append(count, record.glucose);
                count++;
                if (count >= 100) break;
            }
        }

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->createDefaultAxes();
        chart->setTitle("Glucose Levels (Sorted, Max 100 points)");
        chart->legend()->hide();
        chart->setBackgroundBrush(QBrush(QColor(250, 254, 255)));

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->setFixedSize(600, 480);
        layout->insertWidget(1, chartView);
    }

    void showPieChart(QVBoxLayout* layout, const std::vector<DataRecord>& data) {
        QPieSeries *series = new QPieSeries();

        double diabetes_percentage = dia_rate(data);

        series->append("Has Diabetes", diabetes_percentage);
        series->append("No Diabetes", 100.0 - diabetes_percentage);

        vector<QColor> pieColors = {QColor(211, 205, 241), QColor(201, 223, 247)};
        const auto &slices = series->slices();

        for (int i = 0; i < slices.size(); ++i) {
            QPieSlice *slice = slices[i];
            slice->setLabelVisible(true);
            slice->setLabel(
                QString("%1 (%2%)")
                    .arg(slice->label())
                    .arg(slice->percentage() * 100, 0, 'f', 1)
                );
            slice->setColor(pieColors[i % pieColors.size()]);
        }

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle(QString("Diabetes Rate for Filtered Group (n=%1)").arg(data.size()));

        QChartView *chartView = new QChartView(chart);
        chart->setBackgroundBrush(QBrush(QColor(250, 254, 255)));
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->setFixedSize(600, 480);
        layout->insertWidget(1, chartView);
    }

    void showBarChart(QVBoxLayout* layout, const std::vector<DataRecord>& data) {
        std::map<int, int> ageGroups;
        for (const auto& record : data) {
            int age = record.age;
            if (age < 0) continue;
            int decade = (age / 10) * 10;
            ageGroups[decade]++;
        }

        QBarSet *set0 = new QBarSet("Patient Count");
        set0->setColor(QColor(204, 237, 252));
        QStringList categories;

        for (auto const& [decade, count] : ageGroups) {
            *set0 << count;
            categories << QString("%1s").arg(decade);
        }

        QBarSeries *series = new QBarSeries();
        series->append(set0);

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Age Distribution by Decade (Filtered)");

        // Add X axis, categories
        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        axisX->append(categories);
        axisX->setTitleText("Age Groups");
        axisX->setTitleBrush(QBrush(QColor(140, 180, 220)));
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        // Add Y axis, count
        QValueAxis *axisY = new QValueAxis();
        axisY->setLabelFormat("%i");
        axisY->setTitleText("Number of People with Diabetes");
        axisY->setTitleBrush(QBrush(QColor(140, 180, 220)));
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);

        chart->legend()->setVisible(false);

        QChartView *chartView = new QChartView(chart);
        chart->setBackgroundBrush(QBrush(QColor(250, 254, 255)));
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->setFixedSize(600, 480);
        layout->insertWidget(1, chartView);
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    WelcomeWindow welcomeWindow;
    welcomeWindow.show();

    return a.exec();
}
