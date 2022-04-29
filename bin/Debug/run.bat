@echo off

echo "Iniciando script" %DATE% %TIME%

set n_nodos=10000
set beta_min=0.1
set beta_max=1.0
set n_steps=10
::set W=0.4
set tr=3
::set archivo=output_%n_nodos%_%%i.txt
set archivo=output_%n_nodos%.txt

FOR /L %%i IN (1, 1, 10) DO call Redes.exe %n_nodos% %tr% %beta_min% %beta_max% %n_steps% %%i %archivo%

::all Redes.exe %n_nodos% 2 %beta_min% %beta_max% %n_steps% %archivo%

echo "Finalizando script" %DATE% %TIME%
pause


