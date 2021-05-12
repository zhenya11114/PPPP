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
		for (int i = 0; i < adsList.size(); ++i) {
			if (get<0>(adsList.at(i)) == id) {
				adsList.erase(adsList.begin() + i);
				return true;
			}
		}
	}
	bool changeAd(size_t id, string name, double price) {
		for (int i = 0; i < adsList.size(); ++i) {
			if (get<0>(adsList.at(i)) == id) {
				get<1>(adsList.at(i)) = name;
				get<2>(adsList.at(i)) = price;
				return true;
			}
		}
	}
	tuple<size_t, string, double>& getAd(size_t id) {
		for (int i = 0; i < adsList.size(); ++i) {
			if (get<0>(adsList.at(i)) == id) {
				return adsList.at(i);
			}
		}
	}

	bool addCountAd(size_t id, string name, size_t countShowns) {
		adsCountList.push_back(make_tuple(id, name, countShowns));

		return true;
	}
	bool removeCountAd(size_t id) {
		for (int i = 0; i < adsCountList.size(); ++i) {
			if (get<0>(adsCountList.at(i)) == id) {
				adsCountList.erase(adsCountList.begin() + i);
				return true;
			}
		}
	}
	bool changeCountAd(size_t id, string name, size_t countShowns) {
		for (int i = 0; i < adsCountList.size(); ++i) {
			if (get<0>(adsCountList.at(i)) == id) {
				get<1>(adsCountList.at(i)) = name;
				get<2>(adsCountList.at(i)) = countShowns;
				return true;
			}
		}
	}
	tuple<size_t, string, double>& getAd(size_t id) {
		for (int i = 0; i < adsList.size(); ++i) {
			if (get<0>(adsList.at(i)) == id) {
				return adsList.at(i);
			}
		}
	}

private:
	vector<tuple<size_t, string, double>> adsList;
	vector<tuple<size_t, string, size_t>> adsCountList;
};

class Copyrighter {
public:
	bool requireDemonetization(size_t id) {
		demonetizeList.push_back(id);
	}
	bool undoDemonetization(size_t id) {
		for (int i = 0; i < demonetizeList.size(); ++i) {
			if (demonetizeList.at(i) == id) {
				demonetizeList.erase(demonetizeList.begin() + i);
				return true;
			}
		}
	}

	bool requireVideoBan(size_t id) {
		banList.push_back(id);
	}
	bool undoVideoBan(size_t id) {
		for (int i = 0; i < banList.size(); ++i) {
			if (banList.at(i) == id) {
				banList.erase(banList.begin() + i);
				return true;
			}
		}
	}

	bool addPaidContent(size_t id, double time, double price) {
		paidContentList.push_back(make_tuple(id, time, price));

		return true;
	}
	bool removePaidContent(size_t id) {
		for (int i = 0; i < paidContentList.size(); ++i) {
			if (get<0>(paidContentList.at(i)) == id) {
				paidContentList.erase(paidContentList.begin() + i);
				return true;
			}
		}
	}
	bool changePaidContent(size_t id, double time, double price) {
		for (int i = 0; i < paidContentList.size(); ++i) {
			if (get<0>(paidContentList.at(i)) == id) {
				get<1>(paidContentList.at(i)) = time;
				get<2>(paidContentList.at(i)) = price;
				return true;
			}
		}
	}
	tuple<size_t, double, double>& getAd(size_t id) {
		for (int i = 0; i < paidContentList.size(); ++i) {
			if (get<0>(paidContentList.at(i)) == id) {
				return paidContentList.at(i);
			}
		}
	}
private:
	vector<size_t> demonetizeList;
	vector<size_t> banList;
	vector<tuple<size_t, double, double>> paidContentList;
};

class ContentMaker {
public:
	bool addVideo(size_t id, string name, double price) {
		videos.push_back(make_tuple(id, name, price));

		return true;
	}
	bool removeVideo(size_t id) {
		for (int i = 0; i < videos.size(); ++i) {
			if (get<0>(videos.at(i)) == id) {
				videos.erase(videos.begin() + i);
				return true;
			}
		}
	}
	bool changeVideo(size_t id, string name) {
		for (int i = 0; i < videos.size(); ++i) {
			if (get<0>(videos.at(i)) == id) {
				get<1>(videos.at(i)) = name;
				return true;
			}
		}
	}
	tuple<size_t, string, double>& getVideo(size_t id) {
		for (int i = 0; i < videos.size(); ++i) {
			if (get<0>(videos.at(i)) == id) {
				return videos.at(i);
			}
		}
	}

	bool subscribePrime(double primeCost) {
		if (moneyLeft - primeCost >= 0) {
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
	}

	bool payMoney(double summ) {
		if (moneyLeft + summ >= 0) {
			moneyLeft += summ;
			return true;
		}
		return false;
	}
	
private:
	bool isPrime = false;
	bool isTwoAdsMode = false;
	double moneyLeft = 0;
	vector<tuple<size_t, string, double>> videos;
};

class User {
	bool subscribePrime(double primeCost) {
		isPrime = true;
		return true;
	}
	bool unsubscribePrime() {
		isPrime = false;
		return true;
	}
	bool getPrimeStatus() {
		return isPrime;
	}

	bool isPrime = false;
};

class Hosting {
public:
	bool addAdMaker(size_t id, AdMaker adMaker) {
		adMakers.push_back(make_pair(id, adMaker));

		return true;
	}
	bool removeAdMaker(size_t id) {
		for (int i = 0; i < adMakers.size(); ++i) {
			if (get<0>(adMakers.at(i)) == id) {
				adMakers.erase(adMakers.begin() + i);
				return true;
			}
		}
	}
	AdMaker& getAdMaker(size_t id) {
		for (int i = 0; i < adMakers.size(); ++i) {
			if (get<0>(adMakers.at(i)) == id) {
				return get<1>(adMakers.at(i));
			}
		}
	}

	bool addCopyrighter(size_t id, Copyrighter adMaker) {
		copyrighters.push_back(make_pair(id, adMaker));

		return true;
	}
	bool removeCopyrighter(size_t id) {
		for (int i = 0; i < copyrighters.size(); ++i) {
			if (get<0>(copyrighters.at(i)) == id) {
				copyrighters.erase(copyrighters.begin() + i);
				return true;
			}
		}
	}
	Copyrighter& getCopyrighter(size_t id) {
		for (int i = 0; i < copyrighters.size(); ++i) {
			if (get<0>(copyrighters.at(i)) == id) {
				return get<1>(copyrighters.at(i));
			}
		}
	}

	bool addContentMaker(size_t id, ContentMaker adMaker) {
		contentMakers.push_back(make_pair(id, adMaker));

		return true;
	}
	bool removeContentMaker(size_t id) {
		for (int i = 0; i < contentMakers.size(); ++i) {
			if (get<0>(contentMakers.at(i)) == id) {
				contentMakers.erase(contentMakers.begin() + i);
				return true;
			}
		}
	}
	ContentMaker& getContentMaker(size_t id) {
		for (int i = 0; i < contentMakers.size(); ++i) {
			if (get<0>(contentMakers.at(i)) == id) {
				return get<1>(contentMakers.at(i));
			}
		}
	}

	bool addUser(size_t id, User adMaker) {
		users.push_back(make_pair(id, adMaker));

		return true;
	}
	bool removeUser(size_t id) {
		for (int i = 0; i < users.size(); ++i) {
			if (get<0>(users.at(i)) == id) {
				users.erase(users.begin() + i);
				return true;
			}
		}
	}
	User& getUser(size_t id) {
		for (int i = 0; i < users.size(); ++i) {
			if (get<0>(users.at(i)) == id) {
				return get<1>(users.at(i));
			}
		}
	}

	void serveUser(User user) {

	}
private:
	vector<pair<size_t, AdMaker>> adMakers;
	vector<pair<size_t, Copyrighter>> copyrighters;
	vector<pair<size_t, ContentMaker>> contentMakers;
	vector<pair<size_t, User>> users;
};

int main() {

}