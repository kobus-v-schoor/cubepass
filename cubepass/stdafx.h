#pragma once

//System includes
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <chrono>

//cube-lib includes
#include <dchain/dchain.h>
#include <inip.h>
#include <nihdb/nihdb.h>

//Qt includes
#include <QDialog>
#include <QMainWindow>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QFileDialog>
#include <QDateTime>

//Global declares
extern std::string SETTINGS_FILE;
extern std::string DATABASE_FILE;
#define VERSION "4.0.0"
