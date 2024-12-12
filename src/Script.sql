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

-- Script d'insertion

    use RestaurantManagement;

    INSERT INTO orders (order_id, notification_id, customer_id, menu_id, quantity, order_date, status)
    VALUES
        (1, 1, 1, 2, '1 plate', '2024-12-10 12:00:00', 'Completed'),
        (2, 2, 2, 1, '1 plate', '2024-12-10 12:05:00', 'Pending'),
        (3, 3, 3, 3, '1 plate', '2024-12-10 12:10:00', 'Completed'),
        (4, 4, 4, 1, '1 plate', '2024-12-10 12:15:00', 'Pending'),
        (5, 5, 5, 2, '1 plate', '2024-12-10 12:20:00', 'Completed'),
        (6, 6, 6, 1, '1 plate', '2024-12-10 12:25:00', 'Pending'),
        (7, 7, 7, 4, '1 plate', '2024-12-10 12:30:00', 'Pending'),
        (8, 8, 8, 2, '1 plate', '2024-12-10 12:35:00', 'Completed'),
        (9, 9, 9, 3, '1 plate', '2024-12-10 12:40:00', 'Completed'),
        (10,10, 10, 3, '1 plate', '2024-12-10 12:45:00', 'Completed');

    INSERT INTO payments (payment_id, order_id, payment_date, amount, payment_method)
    VALUES
        (1, 1, '2024-12-10 12:00:00', '2000 FCFA', 'Cash'),
        (2, 2, '2024-12-10 12:05:00', '1500 FCFA', 'Credit Card'),
        (3, 3, '2024-12-10 12:10:00', '1000 FCFA', 'Mobile Payment'),
        (4, 4, '2024-12-10 12:15:00', '1500 FCFA', 'Cash'),
        (5, 5, '2024-12-10 12:20:00', '2000 FCFA', 'Credit Card'),
        (6, 6, '2024-12-10 12:25:00', '1500 FCFA', 'Mobile Payment'),
        (7, 7, '2024-12-10 12:30:00', '3000 FCFA', 'Cash'),
        (8, 8, '2024-12-10 12:35:00', '2000 FCFA', 'Credit Card'),
        (9, 9, '2024-12-10 12:40:00', '1000 FCFA', 'Mobile Payment'),
        (10, 10, '2024-12-10 12:45:00', '1000 FCFA', 'Cash');

INSERT INTO customers (customer_id,name, phone, email)
VALUES
    (1,'John Doe', '634567890', 'johndoe@gmail.com'),
    (2,'Jane Smith', '645678901', 'janesmith@gmail.com'),
    (3,'Alice Johnson', '656789012', 'alicejohnson@gmail.com'),
    (4,'Bob Brown', '667890123', 'bobbrown@gmail.com'),
    (5,'Charlie Davis', '677901234', 'charliedavis@gmail.com'),
    (6,'David White', '689012345', 'davidwhite@gmail.com'),
    (7,'Emma Clark', '690123456', 'emmaclark@gmail.com'),
    (8,'Frank Green', '601234567', 'frankgreen@gmail.com'),
    (9,'Grace Lewis', '612345678', 'gracelewis@gmail.com'),
    (10,'Harry Walker', '653456789', 'harrywalker@gmail.com'),
    (11,'Isla Hall', '634567891', 'islahall@gmail.com'),
    (12,'Jack Young', '645678902', 'jackyoung@gmail.com'),
    (13,'Kara King', '656789013', 'karaking@gmail.com'),
    (14,'Liam Scott', '667890124', 'liamscott@gmail.com'),
    (15,'Mia Adams', '678901235', 'miaadams@gmail.com');


INSERT INTO employees (name, role, hire_date)
VALUES
    -- Manager and Maître d’hôtel
    ('Alice Johnson', 'Manager', '2023-01-01'),
    ('Robert Brown', 'Host', '2023-02-01'), -- Maître d’hôtel

    -- Chefs (Kitchen staff)
    ('David Smith', 'Chef', '2023-03-01'), -- Head Chef (Poste fixe)
    ('Emma Taylor', 'Chef', '2023-03-02'), -- Chef de Partie (Desserts)
    ('Jack White', 'Chef', '2023-03-03'), -- Chef de Partie (Main Dishes)
    ('Sophia Green', 'Chef', '2023-03-04'), -- Chef de Partie (Starters)
    ('Liam Black', 'Chef', '2023-03-05'), -- Sous Chef

    -- Waitstaff and Floor Staff
    ('Mia Roberts', 'Waiter', '2023-04-01'), -- Handles smaller tables
    ('James Harris', 'Waiter', '2023-04-02'), -- Handles larger tables
    ('Oliver Adams', 'Waiter', '2023-04-03'),
    ('Charlotte Johnson', 'Waiter', '2023-04-04'),

    -- Cleaners
    ('Emily Clark', 'Cleaner', '2023-05-01'), -- Cleans dining area
    ('Benjamin Lewis', 'Cleaner', '2023-05-02'), -- Cleans kitchen

    -- Commis Roles
    ('Lucas Wilson', 'Waiter', '2023-06-01'), -- Supports busy waiters
    ('Amelia Martinez', 'Cleaner', '2023-06-02'); -- Supports during peak hours

UPDATE orders
SET employee_id =
        CASE
            WHEN order_id % 3 = 1 THEN 8 -- Mia Roberts
            WHEN order_id % 3 = 2 THEN 9 -- James Harris
            ELSE 11 -- Oliver Adams
            END
WHERE status IN ('Pending', 'Completed');


UPDATE orders
SET employee_id =
        CASE
            WHEN menu_id = 1 THEN 3 -- David Smith
            WHEN menu_id = 2 THEN 4 -- Emma Taylor
            WHEN menu_id = 3 THEN 5 -- Jack White
            WHEN menu_id = 4 THEN 6 -- Sophia Green
            END
WHERE status = 'Pending';



INSERT INTO menu (name, date, plates_per_service)
VALUES
    ('Crab Puff Pastry Menu', '2024-12-11', 100),
    ('Baked Eggs Menu', '2024-12-12', 50),
    ('Fish or Eel Stew Menu', '2024-12-13', 100),
    ('Boles de Picoulats Menu', '2024-12-14', 50);


INSERT INTO recipes (title, preparation_time, cooking_time, is_active)
VALUES
    ('Crab Puff Pastry', 10, 20, TRUE),
    ('Baked Eggs', 10, 5, TRUE),
    ('Fish or Eel Stew', 10, 20, TRUE),
    ('Boles de Picoulats', 60, 25, TRUE);


INSERT INTO recipe_ingredients (recipe_id, ingredient_id, quantity, unit)
VALUES
    -- Crab Puff Pastry
    (1, 11, 300, 'grams'), -- Puff Pastry
    (1, 5, 2, 'whole'), -- Eggs
    (1, 9, 3, 'tablespoons'), -- Fresh Cream
    (1, 12, 2, 'tablespoons'), -- Breadcrumbs
    (1, 7, 2, 'pieces'), -- Onions
    (1, 1, 120, 'grams'), -- Crab Meat
    (1, 19, 1, 'whole'), -- Lemon Juice
    (1, 18, 3, 'pinch'), -- Chopped Parsley
    (1, 16, 1, 'pinch'), -- Cayenne Pepper
    (1, 14, 1, 'pinch'), -- Salt


    -- Baked Eggs
    (2, 5, 4, 'whole'), -- Eggs (one per person)
    (2, 10, 1, 'packets'), -- Grated Cheese
    (2, 9, 3, 'tablespoons'), -- Fresh Cream
    (2, 14, 1, 'pinch'), -- Salt


    -- Fish or Eel Stew

    (3, 4, 10, 'pieces'), -- Fish varieties
    (3, 8, 4, 'heads'), -- Garlic
    (3, 13, 5, 'kg'), -- Flour
    (3, 24, 50, 'grams'), -- Lard
    (3, 14, 1, 'pinch'), -- Salt
    (3, 15, 1, 'pinch'), --  Pepper
    (3, 17, 1, 'sachets'), -- Chili Pepper
    (3, 6, 6, 'medium sizes'), -- Potatoes

    -- Boles de Picoulats
    (4, 3, 2, 'kg'), -- Sausage Meat
    (4, 24, 5, 'kg'), -- Ground Beef
    (4, 7, 2, 'pieces'), -- Onions
    (4, 8, 3, 'heads'), -- Garlic
    (4, 5, 2, 'whole'), -- Eggs
    (4, 14, 1, 'pinch'), -- Salt
    (4, 13, 1, 'kg'), -- Flour
    (4, 22, 1, 'tubes'), -- Tomato Paste
    (4, 21, 1, 'glass'), -- Red Wine Vinegar
    (4, 23, 2, 'cubes'), -- Beef Bouillon
    (4, 20, 100, 'ml'); -- Sunflower Oil


INSERT INTO ingredients (ingredient_id, name, unit, restock_threshold)
VALUES
    (1, 'Crab meat', '300g', 10),
    (2, 'Minced beef', '10kg', 2),
    (3, 'Sausage meat', '10kg', 2),
    (4, 'Fish varieties', '100 pieces', 10),
    (5, 'Eggs', '10', 3),
    (6, 'Potatoes', '15 medium sizes', 5),
    (7, 'Onions', '6', 2),
    (8, 'Garlic', '15 heads', 2),
    (9, 'Crème fraîche', '6 tablespoons', 2),
    (10, 'Grated cheese', '5 packets', 2),
    (11, 'Puff pastry', '500 grams', 100),
    (12, 'Breadcrumbs', '5 tablespoons', 2),
    (13, 'Flour', '100kg', 10),
    (14, 'Salt', '20 grams', 10),
    (15, 'Pepper', '20 grams', 10),
    (16, 'Cayenne pepper', '20 grams', 10),
    (17, 'Chili', '10 sachets', 5),
    (18, 'Parsley', '5 packets', 5),
    (19, 'Lemon juice', '20 lemons', 10),
    (20, 'Sunflower oil', '250 milliliters', 50),
    (21, 'Red wine vinegar', '120 milliliters', 20),
    (22, 'Tomato concentrate', '30 tubes', 5),
    (23, 'Beef bouillon cubes', '5 cubes', 2),
    (24, 'Lard', '20 grams', 10);


