#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <map>
#include <iostream>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

// In-memory storage for items
std::map<int, json::value> items = {
    {1, json::value::string(U("Item 1"))},
    {2, json::value::string(U("Item 2"))},
    {3, json::value::string(U("Item 3"))}
};

void handle_get(http_request request) {
    json::value response = json::value::object();
    response[U("items")] = json::value::array();

    int index = 0;
    for (const auto& item : items) {
        response[U("items")][index++] = item.second;
    }

    request.reply(status_codes::OK, response);
}

void handle_post(http_request request) {
    request.extract_json().then([=](json::value json_data) {
        // Assign a new ID to the item
        int new_id = items.size() + 1;
        items[new_id] = json_data;
        items[new_id][U("id")] = json::value::number(new_id);

        json::value response = json::value::object();
        response[U("message")] = json::value::string(U("Item created"));
        response[U("id")] = json::value::number(new_id);
        
        request.reply(status_codes::Created, response);
    }).wait();
}

void handle_delete(http_request request) {
    auto id_str = uri::split_path(request.relative_uri().path()).back();
    int id = std::stoi(id_str);
    
    json::value response = json::value::object();
    
    if (items.erase(id) > 0) {
        response[U("message")] = json::value::string(U("Item deleted"));
        request.reply(status_codes::OK, response);
    } else {
        response[U("message")] = json::value::string(U("Item not found"));
        request.reply(status_codes::NotFound, response);
    }
}

int main() {
    uri_builder uri(U("http://localhost:8080/api/items"));
    auto addr = uri.to_uri().to_string();
    http_listener listener(addr);

    listener.support(methods::GET, handle_get);
    listener.support(methods::POST, handle_post);
    listener.support(methods::DEL, handle_delete);  // Support DELETE method

    try {
        listener
            .open()
            .then([&listener]() {
                std::wcout << L"Server listening at: " << listener.uri().to_string().c_str() << std::endl;
            })
            .wait();

        std::string line;
        std::getline(std::cin, line);  // Wait for user input to stop the server
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }

    return 0;
}
