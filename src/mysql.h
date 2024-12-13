#include <iostream>

void resetDatabase() {
    MYSQL *conn = mysql_init(nullptr);
    if (conn == nullptr) {
        std::cerr << "mysql_init() failed\n";
        return;
    }

    if (mysql_real_connect(conn, "localhost", "root", "password", "restaurant_db", 0, nullptr, 0) == nullptr) {
        std::cerr << "mysql_real_connect() failed\n";
        mysql_close(conn);
        return;
    }

    // Execute reset script
    if (mysql_query(conn, "SOURCE reset_database.sh")) {
        std::cerr << "Database reset failed: " << mysql_error(conn) << "\n";
    } else {
        std::cout << "Database successfully reset.\n";
    }

    mysql_close(conn);
}
