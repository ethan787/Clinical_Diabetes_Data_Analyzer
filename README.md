# Clinical Diabetes Data Analyzer

A C++ application for processing and visualizing clinical diabetes data from large datasets, enabling users to explore health metrics, sort and filter records, and generate statistical insights.

## 🧠 Project Overview

The Clinical Diabetes Data Analyzer is a tool built in **C++** that reads, processes, and visualizes clinical diabetes data from large CSV files. It includes features like:

* Efficient data loading and structured parsing
* Interactive or automated data processing pipelines
* Filtering and sorting based on health metrics
* Visual data inspection and simple analytics

This project is ideal for developers interested in **data analysis pipelines**, **C++ GUI development**, and working with large clinical datasets.

## 🚀 Features

* 🗂️ Scalable data processing for datasets with 100,000+ rows
* 📊 Integrated visualization of health metrics and diabetes likelihood
* ⚙️ Modular design with separate components for stats, filters, and sorting
* 🧩 Uses Qt for cross-platform UI (if compiled with Qt)
* 🧪 Simple CSV dataset integration for quick analysis workflows

## 📦 Tech Stack

* **Language:** C++
* **UI:** Qt (via `.ui` file in `mainwindow.ui`)
* **Build:** CMake (`CMakeLists.txt`)
* **Data Handling:** Custom CSV parser (`CSV.h`)
* **Sorting & Stats Modules:** (`sort.cpp`, `stats.cpp`)
* **Visualization:** UI elements + backend integration

## 📁 Repository Structure

```
├── CMakeLists.txt  
├── main.cpp  
├── backendCSV.cpp / .h  
├── backendpipline.cpp / .h  
├── filters.cpp / .h  
├── sort.cpp / .h  
├── stats.cpp / .h  
├── data_set.h  
├── mainwindow.cpp / .h  
├── mainwindow.ui  
├── diabetes_dataset_with_notes.csv  
└── README.md
```

## ⚙️ Setup & Build

To build and run the project locally:

1. **Install Qt Creator** and the Qt SDK (required for UI and build)

2. Clone the repository:

   ```bash
   git clone https://github.com/ethan787/Clinical_Diabetes_Data_Analyzer.git
   cd Clinical_Diabetes_Data_Analyzer
   ```

3. **Place the dataset**

   * Download the CSV dataset from Kaggle:
     *[https://www.kaggle.com/datasets/ziya07/diabetes-clinical-dataset100k-rows](https://www.kaggle.com/datasets/ziya07/diabetes-clinical-dataset100k-rows)*
   * Place the CSV file into the project’s **build folder** (so the app can load it)

4. Open the project in **Qt Creator**

   * Select `CMakeLists.txt`
   * Configure the kit/toolchain
   * Build & Run the application

5. If graphs don’t display, ensure the CSV file is placed correctly in the compiled binary’s working directory.

## 🧪 Usage

Once built:

* Launch the executable from Qt Creator or the build folder
* Load your diabetes dataset
* Use the UI controls to filter, sort, and visualize health metrics
* Explore statistics for patterns and trends

*(Because the UI is based on Qt, supported widgets and interaction vary based on your Qt setup.)*

## 🧩 Notes & Troubleshooting

* If the project does not compile, verify your **Qt version** and **CMake configuration**
* Ensure the CSV dataset is named correctly and in the expected folder
* Remove the `build` folder and re-run CMake to refresh cache if changes fail
