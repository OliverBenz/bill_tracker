CREATE TABLE shops(
    id INTEGER UNIQUE PRIMARY KEY,
    name TEXT UNIQUE
);

CREATE TABLE category(
    id INTEGER UNIQUE PRIMARY KEY,
    name TEXT UNIQUE
);

CREATE TABLE usage(
    id INTEGER UNIQUE PRIMARY KEY,
    name TEXT,
    categoryId INTEGER,

    FOREIGN KEY (categoryId) REFERENCES category(id),
    UNIQUE (name, categoryId)
);

CREATE TABLE bills(
    id INTEGER UNIQUE PRIMARY KEY,
    date TEXT,
    price REAL,
    shopId INTEGER,
    usageId INTEGER,
    filename TEXT,

    FOREIGN KEY(shopId) REFERENCES shops(id),
    FOREIGN KEY(usageId) REFERENCES usage(id)
);