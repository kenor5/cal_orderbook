#include "./include/getbasic.h"
// #include "./sub-pub/redis_publisher.h"
// #include <boost/archive/text_oarchive.hpp>
// #include <boost/archive/text_iarchive.hpp>
// #include <boost/serialization/string.hpp>
// #include <boost/serialization/vector.hpp>

GetBasic::GetBasic(const std::string& fileName)
{
    // std::cout<<path<<std::endl;
    // if(utils::dirExists(path))
    // {
    //     std::vector<std::string> fileNames;
    //     utils::scanDir(path,fileNames);

    //     for(std::string& fileName : fileNames)
    //     {
            std::cout<<fileName<<std::endl;
            rapidcsv::Document doc(fileName, rapidcsv::LabelParams(-1,-1));
            Trades = std::vector<trade_t>();
            Orders = std::vector<order_t>();
            parse(doc);
        // }
    // }
}


void GetBasic::parse(rapidcsv::Document& doc)
{




    std::vector<char> Datatypes = doc.GetColumn<char>(Base_Datatype_Col);
    std::vector<int> FirstFids = doc.GetColumn<int>(Base_FirstFid_Col);
    std::vector<int> SrcIds = doc.GetColumn<int>(Base_SrcId_Col);
    int sz = Datatypes.size();
    // int counter = 0;
    std::string str;
    // auto fill = [](int i) {std::string rt = std::to_string(i); while (rt.size() < 10) rt = "0"+rt; return rt;};

    for(int row = 0; row < sz; ++row)
    {
        if(Datatypes[row] == 'M') continue; // 过滤Datatype为'M'的数据

        if(SrcIds[row] == 4) continue;  //过滤SrcId为4的数据
        int FirstFid = FirstFids[row];

        if(FirstFid == TradeFid)
        {
          //  if(doc.GetCell<int>(Trade_MsgType_Col,row) != 300192) continue; //过滤MsgType不为300192的数据
            get_Trade(row,doc);
        }
        else if(FirstFid == OrderFid)
        {
            if(doc.GetCell<int>(Order_MsgType_Col,row) != 300192) continue; //过滤MsgType不为300192的数据
            get_Order(row,doc);
        }
        
        // if(trade.size() + order.size() >= 50000&&row<sz-1)
        // {
        //     // std::ostringstream os1, os2;
        //     // order.serialization(os1);
        //     // trade.serialization(os2);
        //     // str = os1.str();

        //     str = fill(str.size()) + str + os2.str();
        //     publisher.publish(channel_name,str);
        //     // sleep(1);
        //     std::cerr << order.size() + trade.size() << '\n';

        //     order.clear();
        //     trade.clear();
        //     // VectorSerialization<trade_t>(trade).swap(trade);
        //     // VectorSerialization<trade_t>(order).swap(order);
        //     counter++;

            
        // }
//        else if(FirstFid == BaseFid)
//        {
//            get_Base(row,doc);
//        }
    }
    // if (order.size()+trade.size() >0) {
    //     std::ostringstream os1, os2;
    //     order.serialization(os1);
    //     trade.serialization(os2);
    //     str = os1.str();

    //     str = fill(str.size()) + str + os2.str();
    //     publisher.publish(channel_name,str);
    //     counter++;
    //     order.clear();
    //     trade.clear();
        // VectorSerialization<trade_t>(trade).swap(trade);
        // VectorSerialization<trade_t>(order).swap(order);
    // }

    // publisher.publish(channel_name, "finish");

    // std::cerr << "counter:" <<  counter << '\n';
    // if (counter >= 15) sleep(200);
    // else if (counter == 0) sleep(3);
    // else  sleep(3*counter);
    // publisher.disconnect();
    // publisher.uninit();
}


void GetBasic::get_Trade(int row,rapidcsv::Document& doc)
{

    time_stamp_t ns = doc.GetCell<long long>(Trade_NanoSecond_Col,row);
    int InstrumentId = doc.GetCell<int>(Trade_InstrumentId_Col,row);
    trade_flag_t flag = (doc.GetCell<char>(Trade_TradeFlag_Col,row) == '4' ? chargeback_flag : deal_flag);
    price_t price = static_cast<int>(doc.GetCell<float>(Trade_Price_Col,row) * 10000);
    int vol =  doc.GetCell<int>(Trade_Vol_Col,row);
    int seq =  doc.GetCell<int>(Trade_SeqNum_Col,row);
    int bid_seq =  doc.GetCell<int>(Trade_BidSeqNum_Col,row);
    int ask_seq =  doc.GetCell<int>(Trade_AskSeqNum_Col,row);
    Trades.emplace_back(ns,InstrumentId,flag,price,vol,seq,bid_seq,ask_seq);
    // trade.emplace_back(ns,InstrumentId,flag,price,vol,seq,bid_seq,ask_seq);
}


void GetBasic::get_Order(int row,rapidcsv::Document& doc)
{
     time_stamp_t ns = doc.GetCell<long long>(Order_NanoSecond_Col,row);
     int InstrumentId = doc.GetCell<int>(Order_InstrumentId_Col,row);
     order_side_t side = (doc.GetCell<char>(Order_Side_Col,row) == '1' ? bid_flag : ask_flag);
     price_t price = static_cast<int>(doc.GetCell<float>(Order_Price_Col,row) * 10000);
     int vol = doc.GetCell<int>(Order_Vol_Col,row);
     order_type_t type;
     {
         char ch = doc.GetCell<char>(Order_OrderType_Col,row);
         if(ch== '1') type = market_flag;
         else if(ch == '2') type = limit_flag;
         else type = best_price_flag;
     }
     int seq = doc.GetCell<int>(Order_SeqNum_Col,row);
     Orders.emplace_back(ns,InstrumentId,side,price,vol,type,seq);
    //  order.emplace_back(ns,InstrumentId,side,price,vol,type,seq);
}

//void GetBasic::get_Base(int row,rapidcsv::Document& doc)
//{
//    time_stamp_t ns = doc.GetCell<long long>(Base_NanoSecond_Col,row);
//    int InstrumentId = doc.GetCell<int>(Base_InstrumentId_Col,row);
//    price_t open_price = static_cast<int>(doc.GetCell<float>(Base_Open_Col,row) * 100);
//    price_t upper_price = static_cast<int>(doc.GetCell<float>(Base_UpperLimit_Col,row) * 100);
//    price_t lower_price = static_cast<int>(doc.GetCell<float>(Base_LowerLimit_Col,row) * 100);
//    price_t pre_close_price = static_cast<int>(doc.GetCell<float>(Base_PreCloseCol,row) * 100);
//    price_t pre_settlement_price = static_cast<int>(doc.GetCell<float>(Base_PreSettlement_Col,row)*100);
//    Bases.back().emplace_back(ns,InstrumentId,open_price,upper_price,lower_price,pre_close_price,pre_settlement_price);
//}

