echo off
echo dumping data...
svnadmin dump "%1">"%1_db.dump"
ren "%1" "%1_BD"

echo creating fsfs repository...
svnadmin create --fs-type fsfs "%1"

echo copying configure file...
copy /Y "%1_BD/conf" "%1/conf"

echo importing dump data...
svnadmin load "%1"<"%1_db.dump"

echo delete dummy files
del /F /Q "%1_db.dump"
rmdir /S /Q "%1_BD"
echo on
