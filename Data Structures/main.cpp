#include "map.h"
#include "N_ary_tree.h"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

struct Game {
    string name;
    string short_description;
    string long_description;
    string genres;
    string minimum_system_requirement;
    string recommend_system_requirement;
    string release_date;
    string developer;
    string publisher;
    string overall_player_rating;
    string number_of_reviews_from_purchased_people;
    string number_of_english_reviews;
    string link;
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
        cerr << "File could not be opened" << endl;
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

        games.push_back(game);
        line = "";
    }
    cout << "Number of Games: " << games.size() << endl;
    cout << "First 5 Games:" << endl;
    cout << games[0].short_description << endl;
    for (int i = 0; i < 5; i++) {
        cout << "Name: " << games[i].name << " || Description: " << games[i].short_description << endl;
    }
    return 0;
}

// int main(){
//     vector<Game> games;
//
//     ifstream file("resources/data/games_description.csv");
//     if (!file.is_open()) {
//         cerr << "File could not be opened" << endl;
//         return 1;
//     }
//     string line;
//     getline(file, line); //reads the header to skip it
//     while (getline(file, line)) {
//         vector<string> dataPoints = readCSVLine(line);
//         if (dataPoints.size() != 13) {
//             cout << "a row didnt have 13 items, contained " << dataPoints.size() << endl;
//             continue;
//         }
//         Game game;
//         game.name = dataPoints[0];
//         game.short_description = dataPoints[1];
//         game.long_description = dataPoints[2];
//         game.genres = dataPoints[3];
//         game.minimum_system_requirement = dataPoints[4];
//         game.recommend_system_requirement = dataPoints[5];
//         game.release_date = dataPoints[6];
//         game.developer = dataPoints[7];
//         game.publisher = dataPoints[8];
//         game.overall_player_rating = dataPoints[9];
//         game.number_of_reviews_from_purchased_people = dataPoints[10];
//         game.number_of_english_reviews = dataPoints[11];
//         game.link = dataPoints[12];
//
//         games.push_back(game);
//         line = "";
//     }
//     cout << "Number of Games: " << games.size() << endl;
//     return 0;
// }