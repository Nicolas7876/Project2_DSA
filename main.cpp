#include "./Data Structures/map.h"
#include "./Data Structures/N_ary_tree.h"
#include <iostream>
#include <string>
#include <fstream>

struct Game {
    string name;
    string short_description;
    string genres;
    string release_date;
    string developer;
    string publisher;
    string overall_player_rating;
    string number_of_reviews_from_purchased_people;
    string link;
    vector<vector<string>> rank_info;
    vector<string> reviews;
    vector<string> genreList;

    void convertGenres() {
        vector<string> genres;
        string genre = "";
        bool inQuote = false;
        for (char c : this->genres) {
            if (c == '[' || c == ']' || c == ',' || c == '\n' || (!inQuote && c == ' ')) {
                continue;
            }
            if (c == '\'' && inQuote == true) {
                inQuote = false;
                this->genreList.push_back(genre);
                genre = "";
                continue;
            }
            if (c == '\'') {
                inQuote = !inQuote;
                continue;
            }

            genre += c;
        }
    }
};

vector<string> readCSVLine(string line) {   //takes in a line, goes char by char to find commas, separates
    vector<string> result;                  //into different categories when it find commas not in quotes
    string cell;                            //result contains each data point in order
    bool inQuotes = false;

    for (int i = 0; i < line.size(); i++) {
        if (line[i] == '"') {
            inQuotes = !inQuotes;
        }
        else if (line[i] == ',' && inQuotes == false) {
            result.push_back(cell);
            cell = "";
        }
        else {
            cell += line[i];
        }
    }
    result.push_back(cell);     //last cell wont be included by default because no closing comma
    return result;
}

int main(){ //test main with altered data file
    vector<Game> games;

    ifstream file("resources/data/games_descriptiontest.csv");  //change this file-path when you do testing
    if (!file.is_open()) {
        cerr << "File1 could not be opened" << endl;
        return 1;
    }
    string line;
    getline(file, line); //reads the header to skip it
    while (getline(file, line)) {
        vector<string> dataPoints = readCSVLine(line);
        if (dataPoints.size() != 9) {
            cout << "a row didnt have 9 items, contained " << dataPoints.size() << endl;
            continue;
        }
        Game game;
        game.name = dataPoints[0];
        game.short_description = dataPoints[1];
        game.genres = dataPoints[2];
        game.release_date = dataPoints[3];
        game.developer = dataPoints[4];
        game.publisher = dataPoints[5];
        game.overall_player_rating = dataPoints[6];
        game.number_of_reviews_from_purchased_people = dataPoints[7];
        game.link = dataPoints[8];
        game.convertGenres();
        games.push_back(game);
        line = "";
    }
    file.close();

    ifstream file2("resources/data/ranks.csv"); //this compiles rank info into class objects
    if (!file2.is_open()) {
        cerr << "File2 could not be opened" << endl;
        return 1;
    }
    line = "";
    getline(file2, line);
    while (getline(file2, line)) {
        vector<string> ratingPoints = readCSVLine(line);
        if (ratingPoints.size() != 4) {
            cout << "a row didnt have 4 data points, contained: " << ratingPoints.size() << endl;
            continue;
        }
        for (Game &game : games) {
            if (game.name == ratingPoints[0]) {
                vector<string> ranking = {ratingPoints[1], ratingPoints[2], ratingPoints[3]};
                game.rank_info.push_back(ranking);
                // cout << "game (" << game.name << ") ranked " << ratingPoints[3] << " in: " << ratingPoints[2] << " for " << ratingPoints[1] << endl;
            }
            else {
                // cout << "game " << game.name << " didnt have a ranking" << endl;
            }
        }
        line = "";
    }
    file2.close();

    ifstream file3("resources/data/reviews.csv");
    if (!file3.is_open()) {
        cerr << "File3 could not be opened" << endl;
        return 1;
    }
    line = "";
    getline(file3, line);
    while (getline(file3, line)) {
        vector<string> reviewData = readCSVLine(line);
        if (reviewData.size() != 2) {
            cout << "a row didnt have 2 data points, contained: " << reviewData.size() << endl;
            continue;
        }
        for (Game &game : games) {
            if (game.name == reviewData[0]) {
                game.reviews.push_back(reviewData[1]);
            }
        }
    }
    file3.close();
    
    //test game names
    // cout << "Number of Games: " << games.size() << endl;
    // cout << "First 5 Games:" << endl;
    // cout << games[0].short_description << endl;


    // test rankings
    // int numlines = 0;
    //  for (int i = 0; i < games.size(); i++) {
    //      if (games[i].rank_info.size() != 0) {
    //          for (int j = 0; j < games[i].rank_info.size(); j++) {
    //              cout << "Name: " << games[i].name << " || Rank Info: " << games[i].rank_info[j][2] << " in " << games[i].rank_info[j][1] << " for " << games[i].rank_info[j][0] << endl;
    //              numlines++;
    //          }
    //      }
    //  }
    // cout << numlines << endl;

    //test reviews
    // for (int i = 0; i < 5; i++) {
    //     for (int j = 0; j < games[i].reviews.size(); j++) {
    //         cout << "Game Name: " << games[i].name << ", Review: " << games[i].reviews[j] << endl;
    //     }
    // }

    //genre test
//     cout << games[0].genres << endl;
//     for (string genre : games[0].genreList) {
//         cout << genre << endl;
//     }
    return 0;
}
