-- Créer la base de données
CREATE DATABASE RestaurantManagement;
USE RestaurantManagement;

-- Table pour les recettes
CREATE TABLE recipes (
    recipe_id INT AUTO_INCREMENT PRIMARY KEY,
    title VARCHAR(255) NOT NULL,
    preparation_time INT NOT NULL, -- en minutes
    cooking_time INT NOT NULL, -- en minutes
    is_active BOOLEAN DEFAULT TRUE
);

-- Table pour les ingrédients
CREATE TABLE ingredients (
    ingredient_id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    unit VARCHAR(50) NOT NULL, -- ex. grammes, litres
    restock_threshold INT DEFAULT 10 -- Seuil pour réapprovisionnement
);

-- Table pour gérer la relation recettes-ingrédients
CREATE TABLE recipe_ingredients (
    recipe_id INT,
    ingredient_id INT,
    quantity DECIMAL(10, 2) NOT NULL,
    unit VARCHAR(50) NOT NULL
    PRIMARY KEY (recipe_id, ingredient_id),
    FOREIGN KEY (recipe_id) REFERENCES recipes(recipe_id) ON DELETE CASCADE,
    FOREIGN KEY (ingredient_id) REFERENCES ingredients(ingredient_id) ON DELETE CASCADE
);

-- Table pour les employés
CREATE TABLE employees (
    employee_id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    role ENUM('Waiter', 'Host', 'Cleaner', 'Manager', 'Chef') NOT NULL,
    hire_date DATE NOT NULL
);


-- Table pour les clients
CREATE TABLE customers (
    customer_id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    phone VARCHAR(15),
    email VARCHAR(255),
   
);

-- Table pour le menu
CREATE TABLE menu (
    menu_id INT AUTO_INCREMENT PRIMARY KEY,
 name VARCHAR(100) NOT NULL,
    date DATE NOT NULL,
    plates_per_service INT DEFAULT 50
);


-- Table pour les commandes
CREATE TABLE orders (
    order_id INT AUTO_INCREMENT PRIMARY KEY,
    notification_id INT,
    customer_id INT,
    menu_id INT,
    employee_id INT,
    quantity VARCHAR(10) NOT NULL, 
    order_date DATETIME DEFAULT CURRENT_TIMESTAMP,
    status ENUM('Pending', 'Completed') DEFAULT 'Pending',
    FOREIGN KEY (customer_id) REFERENCES customers(customer_id) ON DELETE CASCADE,
     FOREIGN KEY (menu_id) REFERENCES menu(menu_id) ON DELETE CASCADE,
     FOREIGN KEY (employee_id) REFERENCES employees(employee_id) ON DELETE CASCADE
     FOREIGN KEY (notification_id) REFERENCES notifications(notification_id) ON DELETE CASCADE
);

-- Table pour les paiements
CREATE TABLE payments (
    payment_id INT AUTO_INCREMENT PRIMARY KEY,
    order_id INT,
    payment_date DATETIME DEFAULT CURRENT_TIMESTAMP,
    amount VARCHAR(20) NOT NULL, -- in FCFA
    payment_method ENUM('Cash', 'Credit Card', 'Mobile Payment') NOT NULL,
    FOREIGN KEY (order_id) REFERENCES orders(order_id) ON DELETE CASCADE
);

-- Tables pour les Notifications 
CREATE TABLE notifications (
    notification_id INT AUTO_INCREMENT PRIMARY KEY,
    order_id INT, 
    message TEXT NOT NULL,
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    is_read BOOLEAN DEFAULT FALSE,
    FOREIGN KEY (order_id) REFERENCES orders(order_id) ON DELETE CASCADE
);


