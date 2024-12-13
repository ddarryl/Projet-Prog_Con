struct Table {
    int id;
    bool reserved;
    explicit Table(int id) : id(id), reserved(false) {}
};