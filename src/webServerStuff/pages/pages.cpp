#include "pages.h"

String Page404 = "<!DOCTYPE html><html> <head> <title>Not found</title> <meta charset=\"utf-8\"></head> <body> <h1>404 Not Found</h1> <p>The requested resource was not found on this device.</p> <p>Запрошенный ресурс не найден на устройстве.</p> </body></html>";

String PageChange = "<!DOCTYPE html><html> <head> <title>BikePC Смена настроек</title> <meta charset=\"utf-8\"><meta http-equiv=\"refresh\" content=\"5;URL=/\" /> </head> <body> <table align=center> <tr> <td><h1>BikePC Смена настроек</h1></td> </tr> <tr> <td><h3>Ваши настройки были изменены.</h3></td> </tr> <tr> <td> Вы будете перенаправлены на главную страницу через 5 секунд. </td> </tr> </table> </body></html>";

String PageSwitch = "<!DOCTYPE html><html> <head> <title>BikePC Смена режима</title> <meta charset=\"utf-8\"></head> <body> <table align=center> <tr> <td><h1>BikePC Смена режима</h1></td> </tr> <tr> <td><h3>Режим подкючения устройства был изменён.</h3></td> </tr> </table> </body></html>";

String PageHardReset = "<!DOCTYPE html><html> <head> <title>Reset device</title> <meta charset=\"utf-8\"><meta http-equiv=\"refresh\" content=\"15;URL=/\" /> </head> <body> <table align=center> <tr> <td><h1>Device's setting and data is reset to factory</h1></td> </tr><tr> <td><h1>Настройки и данные устройства сброшены до заводских</h1></td> </tr> <tr> <td> Device will be in AP mode with default settings.<br> Time and Date Cleared.<br> SD Card Data stays saved.<br> </td> </tr><tr><td></td></tr><tr> <td> Устройство будет находиться в режиме Точки Доступа.<br> Время и дата сброшены.<br> Данные SD карты НЕ будут удалены.<br> </td> </tr> </table> </body></html>";

String PageIndex1 = "<!DOCTYPE html><html> <head> <title>BikePC</title> <meta charset=\"utf-8\"><style>a {text-decoration: none;color: black;}.button{width:75%;border:1px solid rgba(255,255,255,0.50);background-color: rgba(255,255,255,0.50);text-align: center;}.fill{height: 7px}</style> </head> <body><div style=\"width: 99%; text-align: center\"><h1>ESP8266 BikeComputer</h1></div>";
String PageHeader1 = "<div style=\"text-align: center\"><h2>Батарея: ";
String PageHeaderBattery = ""; //number
String PageHeader2 = "%</h2></div><div style=\"text-align: center\"><h2>";
String PageHeaderDate = ""; //dd/mm/yy
String PageHeader3 = "</h2></div><div style=\"text-align: center\"><h2>";
String PageHeaderTime = ""; //hh:mm
String PageHeader4 = ", ";
String PageHeaderDOTW = ""; //day of the week
String PageHeader5 = "</h2></div><div style=\"padding-left: 20%; padding-top: 1%; padding-bottom: 1%; background-color: #969696;\"><a href=\"/\"><div class=\"button\"><h3>Домой</h3></div></a><div class=\"fill\"></div><a href=\"/stats\"><div class=\"button\"><h3>Статистика</h3></div></a><div class=\"fill\"></div><a href=\"/get_settings\"><div class=\"button\"><h3>Настройки</h3></div></a><div class=\"fill\"></div><a href=\"/info\"><div class=\"button\"><h3>Инфо</h3></div></a></div>";
String PageIndex2 = "</body></html>";

//separated pages
//stats no graph
String PageStats1 = "<!DOCTYPE html><html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"><title>BikePC Статистика</title><style>a{text-decoration: none;color: black;}.button{width:75%;border:1px solid rgba(255,255,255,0.50);background-color: rgba(255,255,255,0.50);text-align: center;}.fill{height: 7px}.block{border:3px solid black;border-bottom: none;text-align: center;padding-bottom: 5%}</style></head> <body><div style=\"width: 99%; text-align: center\"><h1>BikePC Статистика</h1></div>";
//insert header
String PageStats2 = "<div class=\"block\"><div><h2>Поездка ";
String PageStatsTripNumber = ""; //number
String PageStats3 = ".</h2></div><div><h2>Поездка: ";
String PageStatsTrip = ""; //number
String PageStats4 = " м</h2></div><div><h2>Время поездки: ";
String PageStatsHours = ""; //hours
String PageStats5 = " ч, ";
String PageStatsMinutes = ""; //mins
String PageStats6 = " мин</h2></div><div><h2>Средняя скорость: ";
String PageStatsAvgSpd = ""; //number
String PageStats7 = " км/ч</h2></div><div><h2>Средний пульс: ";
String PageStatsAvgPulse = ""; //number OR --
String PageStats8 = " уд/м</h2></div><div><h2>ODO: ";
String PageStatsODO = ""; //number
String PageStats9 = " м</h2></div><div><h2>Средний каденс: ";
String PageStatsAvgCad = ""; //number
String PageStats10 = " об/мин</h2></div></div></body></html>";

//settings *****************
String PageSettings1 = "<!DOCTYPE html><html> <head> <title>BikePC Настройки</title><meta charset=\"utf-8\"> <style>a{text-decoration: none;color: black;}.button{width:75%;border:1px solid rgba(255,255,255,0.50);background-color: rgba(255,255,255,0.50);text-align: center;}.fill{height: 7px}.block{border:3px solid black;border-bottom: none;text-align: center;padding-bottom: 5%}.radioChoice div{padding-left: 40%;text-align: left}.spoiler { padding: 0 1em;}.spoiler details { padding: 1em 0;}.spoiler details + details { border-top: 1px solid #e0e0e0;}.spoiler summary { color: black;}.spoiler details div { overflow: hidden; padding: 1em 1em 0;}.spoiler details[open] div { animation: spoiler 1s;}@keyframes spoiler { 0% {max-height: 0;} 100% {max-height: 10em;}}</style> </head> <body><div style=\"width: 99%; text-align: center\"><h1>BikePC Настройки</h1></div>";
//insert header in here
String PageSettings2 = "<div class=\"block\"><h3>Радиус колеса, мм</h3><div><form action=\"/setup\" method=\"POST\"><div><input type=\"tel\" pattern=\"\\d*\" name=\"wheel_radius_cm\" value=\"";
String PageSettingsWheelRadius = ""; //number
String PageSettings3 = "\"/></div><div class=\"fill\"></div><div><input type=\"submit\" value=\"Изменить\"/></div></form></div></div><div class=\"block\"><div class=\"spoiler\"><h3>Период обновления данных</h3><details><summary>Что это?</summary><div>Данные с датчиков выгружаются на SD-карту через определённые вромежутки времени dT.</div></details></div><div><form action=\"/setup\" method=\"POST\"><div class=\"radioCheck\"><div><input type=\"radio\" name=\"sd_dt\" id=\"choice1\" value=\"sd_time_30\"";
String PageSettingsTime30s = "";
String PageSettings4 = "/><label for=\"choice2\">30 секунд</label></div><div><input type=\"radio\" name=\"sd_dt\" id=\"choice2\" value=\"sd_time_60\"";
String PageSettingsTime60s = "";
String PageSettings5 = "/><label for=\"choice3\">1 минута</label></div><div><input type=\"radio\" name=\"sd_dt\" id=\"choice3\" value=\"sd_time_300\"";
String PageSettingsTime5m = "";
String PageSettings6 = "/><label for=\"choice5\">5 минут</label></div><div><input type=\"radio\" name=\"sd_dt\" id=\"choice4\" value=\"sd_time_600\"";
String PageSettingsTime10m = "";
String PageSettings7 = "/><label for=\"choice6\">10 минут</label></div></div><div class=\"fill\"></div><div><input type=\"submit\" value=\"Изменить\"/></div></form></div></div><div class=\"block\"><div><h3>Режим подключения: ";
String PageSettingsWiFiMode = ""; //AP OR Client
String PageSettings8 = "</h3><form action=\"/switch_mode\" method=\"POST\"><input type=\"submit\" value=\"Переключить\"/></form></div></div><div class=\"block\"><div><h3>Установить время и дату</h3><form action=\"/setup\" method=\"POST\"><input type=\"hidden\" name=\"TimeDate\" value=\"true\"><b>Время: </b><input type=\"time\" size=\"30\" name=\"time\" placeholder=\"Set time...\" autocomplete=\"off\" required><p><b>Дата: </b><input type=\"date\" size=\"30\" name=\"date\" placeholder=\"Set date...\" autocomplete=\"off\" required></p><p><input type=\"submit\" value=\"Сменить\"/></p></form></div></div><div class=\"block\"><div><h3>Настройки Точки Доступа</h3><form action=\"/setup\" method=\"POST\"><input type=\"hidden\" name=\"SetType\" value=\"AP\"><b>SSID: </b><input type=\"text\" size=\"30\" name=\"SSID\" placeholder=\"Введите SSID Точки...\" autocomplete=\"off\" required><p><details><summary><b>Что такое SSID?</b></summary><b>SSID</b> - это символьное имя точки доступа.</details></p><p><b>Пароль: </b><input type=\"password\" size=\"30\" name=\"password\" placeholder=\"Введите пароль Точки...\" autocomplete=\"off\" required></p><p><input type=\"submit\" value=\"Изменить настройки Точки Доступа\"/></p></form></div></div><div class=\"block\"><div><h3>Настройки Wi-Fi клиента</h3><form action=\"/setup\"><input type=\"hidden\" name=\"SetType\" value=\"Client\"><b>SSID: </b><input type=\"text\" size=\"30\" name=\"SSID\" placeholder=\"Введите SSID целевого Wi-Fi...\" autocomplete=\"off\" required><p><details><summary><b>Что такое SSID?</b></summary><b>SSID</b> - это символьное имя точки доступа.</details></p><p><b>Password: </b><input type=\"password\" size=\"30\" name=\"password\" placeholder=\"Введите пароль целевого Wi-Fi...\" autocomplete=\"off\" required></p><p><input type=\"submit\" value=\"Изменить настройки клиента\"/></p></form></div></div><div class=\"block\"><h3>Общий пробег, м</h3><div><form action=\"/setup\" method=\"POST\"><div><input type=\"tel\" pattern=\"\\d*\" name=\"odo_m\" value=\"";
String PageSettingsODO = ""; //number
String PageSettings9 ="\"/></div><div class=\"fill\"></div><div><input type=\"submit\" value=\"Накрутить\"/></div></form></div></div><div class=\"block\" style=\"border-bottom: 3px solid black;\"><div><h3>Сброс</h3><details><summary><b>Сброс до заводских настроек</b></summary><details><summary><b style=\"color:darkred;\">Вы уверены?</b></summary><br><br><b style=\"color:red;\">ВСЕ ДАННЫЕ КРОМЕ SD-Карты БУДУТ СБРОШЕНЫ</b><br><br><form action=\"/factory_reset\" method=\"POST\"><input type=\"hidden\" name=\"Confirm\" value=\"true\"><input type=\"submit\" value=\"Сбросить до заводских настроек\"></form></details></details></div></div> </body></html>";