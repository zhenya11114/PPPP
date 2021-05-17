/* YouPoop project
 * all right reserved
 */

#include <iostream>
#include <vector>
#include <tuple>
#include <utility>

using namespace std;

class AdMaker {
public:
	bool addAd(size_t id, string name, double price) {
		adsList.push_back(make_tuple(id, name, price));

		return true;
	}
	bool removeAd(size_t id) {
        for (size_t i = 0; i < adsList.size(); ++i) {
			if (get<0>(adsList.at(i)) == id) {
				adsList.erase(adsList.begin() + i);
				return true;
			}
		}
        return false;
	}
	bool changeAd(size_t id, string name, double price) {
        for (size_t i = 0; i < adsList.size(); ++i) {
			if (get<0>(adsList.at(i)) == id) {
				get<1>(adsList.at(i)) = name;
				get<2>(adsList.at(i)) = price;
				return true;
			}
		}
        return false;
	}
    tuple<size_t, string, double> getAd(size_t id) {
        for (size_t i = 0; i < adsList.size(); ++i) {
			if (get<0>(adsList.at(i)) == id) {
				return adsList.at(i);
			}
		}
        return tuple<size_t, string, double>(-1,"",0);
	}
    vector<tuple<size_t, string, double>> getAdsList(){
        return adsList;
    }

	bool addCountAd(size_t id, string name, size_t countShowns) {
		adsCountList.push_back(make_tuple(id, name, countShowns));

		return true;
	}
	bool removeCountAd(size_t id) {
        for (size_t i = 0; i < adsCountList.size(); ++i) {
			if (get<0>(adsCountList.at(i)) == id) {
				adsCountList.erase(adsCountList.begin() + i);
				return true;
			}
		}
        return false;
	}
	bool changeCountAd(size_t id, string name, size_t countShowns) {
        for (size_t i = 0; i < adsCountList.size(); ++i) {
			if (get<0>(adsCountList.at(i)) == id) {
				get<1>(adsCountList.at(i)) = name;
				get<2>(adsCountList.at(i)) = countShowns;
				return true;
			}
		}
        return false;
	}
    tuple<size_t, string, size_t> getCountAd(size_t id) {
        for (size_t i = 0; i < adsCountList.size(); ++i) {
            if (get<0>(adsCountList.at(i)) == id) {
                return adsCountList.at(i);
			}
		}
        return tuple<size_t, string, size_t>(-1,"",0);
    }
    vector<tuple<size_t, string, size_t>> getAdsCountList(){
        return adsCountList;
    }

private:
	vector<tuple<size_t, string, double>> adsList;
    vector<tuple<size_t, string, size_t>> adsCountList;
};

class Copyrighter {
public:
	bool requireDemonetization(size_t id) {
		demonetizeList.push_back(id);
        return true;
	}
	bool undoDemonetization(size_t id) {
        for (size_t i = 0; i < demonetizeList.size(); ++i) {
			if (demonetizeList.at(i) == id) {
				demonetizeList.erase(demonetizeList.begin() + i);
				return true;
			}
		}
        return false;
	}
    vector<size_t>& getDemonetizeList(){
        return demonetizeList;
    }
    bool isDemonetized(size_t id){
        for (size_t i = 0; i < demonetizeList.size(); ++i) {
            if (demonetizeList.at(i) == id) {
                return true;
            }
        }
        return false;
    }

	bool requireVideoBan(size_t id) {
		banList.push_back(id);
        return true;
	}
	bool undoVideoBan(size_t id) {
        for (size_t i = 0; i < banList.size(); ++i) {
			if (banList.at(i) == id) {
				banList.erase(banList.begin() + i);
				return true;
			}
		}
        return false;
	}
    vector<size_t>& getBanList(){
        return banList;
    }
    bool isBanned(size_t id){
        for (size_t i = 0; i < banList.size(); ++i) {
            if (banList.at(i) == id) {
                return true;
            }
        }
        return false;
    }

	bool addPaidContent(size_t id, double time, double price) {
		paidContentList.push_back(make_tuple(id, time, price));

		return true;
	}
	bool removePaidContent(size_t id) {
        for (size_t i = 0; i < paidContentList.size(); ++i) {
			if (get<0>(paidContentList.at(i)) == id) {
				paidContentList.erase(paidContentList.begin() + i);
				return true;
			}
		}
        return false;
	}
	bool changePaidContent(size_t id, double time, double price) {
        for (size_t i = 0; i < paidContentList.size(); ++i) {
			if (get<0>(paidContentList.at(i)) == id) {
				get<1>(paidContentList.at(i)) = time;
				get<2>(paidContentList.at(i)) = price;
				return true;
			}
		}
        return false;
	}
    tuple<size_t, double, double> getPaidContent(size_t id) {
        for (size_t i = 0; i < paidContentList.size(); ++i) {
			if (get<0>(paidContentList.at(i)) == id) {
				return paidContentList.at(i);
			}
		}
        return tuple<size_t, double, double>(-1,0,0);
    }
    vector<tuple<size_t, double, double>>& getPaidContentList(){
        return paidContentList;
    }
private:
	vector<size_t> demonetizeList;
	vector<size_t> banList;
    vector<tuple<size_t, double, double>> paidContentList;
};

class ContentMaker {
public:
	bool addVideo(size_t id, string name, double price) {
        videoList.push_back(make_tuple(id, name, price));

		return true;
	}
	bool removeVideo(size_t id) {
        for (size_t i = 0; i < videoList.size(); ++i) {
            if (get<0>(videoList.at(i)) == id) {
                videoList.erase(videoList.begin() + i);
				return true;
			}
		}
        return false;
	}
	bool changeVideo(size_t id, string name) {
        for (size_t i = 0; i < videoList.size(); ++i) {
            if (get<0>(videoList.at(i)) == id) {
                get<1>(videoList.at(i)) = name;
				return true;
			}
		}
        return false;
	}
    tuple<size_t, string, double> getVideo(size_t id) {
        for (size_t i = 0; i < videoList.size(); ++i) {
            if (get<0>(videoList.at(i)) == id) {
                return videoList.at(i);
			}
		}
        return make_tuple<size_t, string, double>(0,"",0);
	}
    vector<tuple<size_t, string, double>> getVideoList(){
        return videoList;
    }

	bool subscribePrime(double primeCost) {
        if (payMoney(primeCost)) {
			isPrime = true;
			return true;
		}
		return false;
	}
	bool unsubscribePrime() {
		isPrime = false;
		return true;
	}
	bool getPrimeStatus() {
		return isPrime;
	}

	bool switchTwoAdsMode() {
		isTwoAdsMode = !isTwoAdsMode;
        return isTwoAdsMode;
	}
    bool getTwoAdsMode() {
        return isTwoAdsMode;
    }

	bool payMoney(double summ) {
		if (moneyLeft + summ >= 0) {
			moneyLeft += summ;
			return true;
		}
		return false;
    }
    double getMoneyLeft(){
        return moneyLeft;
    }

private:
	bool isPrime = false;
	bool isTwoAdsMode = false;
	double moneyLeft = 0;
    vector<tuple<size_t, string, double>> videoList;
};

class User {
public:
	bool subscribePrime(double primeCost) {
        if (payMoney(-primeCost)) {
            isPrime = true;
            return true;
        }
        return false;
	}
	bool unsubscribePrime() {
		isPrime = false;
		return true;
	}
	bool getPrimeStatus() {
		return isPrime;
    }

    bool payMoney(double summ) {
        if (moneyLeft + summ >= 0) {
            moneyLeft += summ;
            return true;
        }
        return false;
    }
    double getMoneyLeft(){
        return moneyLeft;
    }
private:
	bool isPrime = false;
    double moneyLeft = 0;
};

class Hosting {
public:
	bool addAdMaker(size_t id, AdMaker adMaker) {
        adMakers.push_back(make_pair(id, adMaker));

		return true;
	}
	bool removeAdMaker(size_t id) {
        for (size_t i = 0; i < adMakers.size(); ++i) {
			if (get<0>(adMakers.at(i)) == id) {
				adMakers.erase(adMakers.begin() + i);
				return true;
			}
		}
        return false;
	}
	AdMaker& getAdMaker(size_t id) {
        for (size_t i = 0; i < adMakers.size(); ++i) {
			if (get<0>(adMakers.at(i)) == id) {
				return get<1>(adMakers.at(i));
			}
        }
        AdMaker* t = new AdMaker();
        return *t;
	}

    bool addCopyrighter(size_t id, Copyrighter copyrighter) {
        copyrighters.push_back(make_pair(id, copyrighter));

		return true;
	}
	bool removeCopyrighter(size_t id) {
        for (size_t i = 0; i < copyrighters.size(); ++i) {
			if (get<0>(copyrighters.at(i)) == id) {
				copyrighters.erase(copyrighters.begin() + i);
				return true;
			}
		}
        return false;
	}
	Copyrighter& getCopyrighter(size_t id) {
        for (size_t i = 0; i < copyrighters.size(); ++i) {
			if (get<0>(copyrighters.at(i)) == id) {
				return get<1>(copyrighters.at(i));
			}
        }
        Copyrighter* t = new Copyrighter();
        return *t;
	}

    bool addContentMaker(size_t id, ContentMaker contentMaker) {
        contentMakers.push_back(make_pair(id, contentMaker));

		return true;
	}
	bool removeContentMaker(size_t id) {
        for (size_t i = 0; i < contentMakers.size(); ++i) {
			if (get<0>(contentMakers.at(i)) == id) {
				contentMakers.erase(contentMakers.begin() + i);
				return true;
			}
		}
        return false;
	}
	ContentMaker& getContentMaker(size_t id) {
        for (size_t i = 0; i < contentMakers.size(); ++i) {
			if (get<0>(contentMakers.at(i)) == id) {
				return get<1>(contentMakers.at(i));
			}
        }
        ContentMaker* t = new ContentMaker();
        return *t;
	}

    bool addUser(size_t id, User user) {
        users.push_back(make_pair(id, user));

		return true;
	}
	bool removeUser(size_t id) {
        for (size_t i = 0; i < users.size(); ++i) {
			if (get<0>(users.at(i)) == id) {
				users.erase(users.begin() + i);
				return true;
			}
		}
        return false;
	}
	User& getUser(size_t id) {
        for (size_t i = 0; i < users.size(); ++i) {
			if (get<0>(users.at(i)) == id) {
				return get<1>(users.at(i));
			}
        }
        User* t = new User();
        return *t;
	}

    void serveUser(User& user, size_t videoId) {
        ////check if vide extist first!!!////

        bool isVideoBanned = false;
        for (size_t i = 0; i < copyrighters.size(); ++i) {
            isVideoBanned = copyrighters.at(i).second.isBanned(videoId);
            if(isVideoBanned == true){
                break;
            }
        }

        bool isUserHavePerm = true;
        bool userPayPrompt = true;//must be random
        if (isVideoBanned) {
            isUserHavePerm = false;
            for (size_t i = 0; i < copyrighters.size(); ++i) {
                tuple<size_t, double, double> content = copyrighters.at(i).second.getPaidContent(videoId);
                if (get<0>(content) == videoId) {
                    if (userPayPrompt) {
                        if (user.payMoney(-get<1>(content))) {
                            isUserHavePerm = true;
                            cout << "user successfully bought access to video\n";
                        }
                        else {
                            cout << "user have not enough money to pay for video shown\n";
                        }
                        break;
                    }
                }
            }
        }
        if (!isUserHavePerm) {
            cout << "video banned\n";
            return;
        }
        else {
            cout << "show video\n";
        }

        bool isShowAds = true;
        if (user.getPrimeStatus()) {
            isShowAds = false;
        }
        else {
            bool primeStatus = false;
            for (size_t i = 0; i < contentMakers.size(); ++i) {
                tuple<size_t, string, double> video = contentMakers.at(i).second.getVideo(videoId);
                if (get<0>(video) == videoId) {
                    primeStatus = true;
                    isShowAds = false;
                    break;
                }
            }
        }

        if (isShowAds) {

        }
        else {

        }
	}
private:
    vector<pair<size_t, AdMaker>> adMakers;
    vector<pair<size_t, Copyrighter>> copyrighters;
    vector<pair<size_t, ContentMaker>> contentMakers;
    vector<pair<size_t, User>> users;
};

int main() {
    Hosting h;

    size_t counter = 0, counter1 = 0, counter2 = 0;
    for (size_t i = 0; i < 3; ++i) {
        AdMaker am;
        am.addAd(counter++, "", 5);
        am.addAd(counter++, "", 5);

        am.addCountAd(counter1++, "", 5);
        am.addCountAd(counter1++, "", 5);

        h.addAdMaker(counter2++, am);
    }

    counter = 0, counter1 = 0, counter2 = 0;
    for (size_t i = 0; i < 3; ++i) {
        Copyrighter cp;
        cp.addPaidContent(counter++, 10, 5);
        cp.addPaidContent(counter++, 10, 5);

        cp.requireDemonetization(counter1++);
        cp.requireVideoBan(counter1++);

        h.addCopyrighter(counter2++, cp);
    }

    counter = 0, counter1 = 0, counter2 = 0;
    for (size_t i = 0; i < 3; ++i) {
        ContentMaker cm;
        cm.addVideo(counter++, "", 5);
        cm.addVideo(counter++, "", 5);

        cm.payMoney(100);
        cm.subscribePrime(5);
        cm.switchTwoAdsMode();

        h.addContentMaker(counter2++, cm);
    }

    User u;
    u.payMoney(100);
//    u.subscribePrime(5);
    h.serveUser(u, 3);
}
