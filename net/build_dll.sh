echo [libusafnet building process]

echo start build libusafnet.so
g++ -g net_new.cpp net_service.cpp accepter.cpp fd_manager.cpp tcprecver.cpp ../thread/thread.cpp -o libusafnet.so -lpthread -std=c++11 -D __LINUX -fPIC -shared
echo [ok]
echo start build demo
g++ -g test_dll.cpp -L . -lusafnet -D __LINUX -o net_test_dll -std=c++11
echo [ok]
echo start config env
cp libusafnet.so /lib/
ldconfig
echo [ok]
