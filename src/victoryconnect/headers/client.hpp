#ifndef _VC_CLIENT_HEADER__
#define _VC_CLIENT_HEADER__
#include <vector>
#include <string>
#include <map>
#include "packet.hpp"

namespace VictoryConnect{

    class Client{
        private: 
            //Vars
            std::string mId;
            std::string mName;

            std::string mDefaultConnection;
            bool mASAP = false;
            int mTickRate = 50;
            bool isTicking = false;

            std::map<std::string, void (*) (Packet packet)> commandListeners;
            std::map<std::string, void (*) (Packet packet)> subscribeListeners; 

            std::vector<Packet> mSendQueue;

            // Functions
            void sendQueue();
            void onCommand();
            void onRequest();
            void onSubmit();
            void onError();
            void startTickLoop();
            void stopTickLoop();
            void onTick();
            void resetTickLoop();

        public:
            Client(std::string id, std::string name);

            void enableUDP(std::string serverIP, int serverPort);
            void enableTCP(std::string serverIP, int serverPort);

            void setDefaultConnection(std::string connnection);
            void setASAP(bool asap);

            void sendPacket(Packet toSend);
            void sendPacket(Packet toSend, std::string connection);

            void newTopic(std::string name, std::string path, std::string connection);
            void setTopic(std::string path, std::string value);
            void setTopic(std::string path, std::vector<std::string> values);
            void subscribe(std::string path, void (*cb) (Packet packet));
            void registerCommand(std::string path, void (*cb)(Packet packet));
            void callCommand(std::string path, std::string value);
            void callCommand(std::string path, std::vector<std::string> values);
            void setTickRate(int tickRate);

            //Get Functions
            std::string getId();
            std::string getName();
            std::string getDefaultConnection();
            bool getASAP();
            int getTickRate();
            std::vector<Packet> getSendQueue();
            int getSendQueueLength();

            bool verifySubscribeListener(std::string path);
            bool verifyCommandListener(std::string path);
    };
}
#endif