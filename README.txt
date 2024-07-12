Admin Mode

Admin mode grants administrators control over various aspects of the cinema operations, including movie listings and snack inventory. The key classes used in Admin mode are:

1. Admin Class
Description: The Admin class grants administrators control over movie listings, enabling them to add, delete, and enter detailed information about movies. Additionally, it allows admins to manage snack inventory by monitoring stock levels and displaying available snacks.

Responsibilities:
Manage movie listings.
Monitor and update snack inventory.

2. Movie Class
Description: This class enables the administrator to input the details for each movie, which can be displayed as necessary, including the name, director, duration, and rating.

Responsibilities:
Input and manage movie details.
3. Snacks Class
Description: The Snacks class serves as a specialized toolbox tailored to manage information regarding snack items. It tracks the quantity of snacks available, their respective prices, and their names.

Responsibilities:
Manage snack inventory.
Track snack quantities and prices.



Customer Mode
Customer mode handles various aspects of client interactions, such as purchasing movie tickets, snacks, and making reservations. The key classes used in 

1. Customer Class
Description: The Customer class handles various aspects of client interactions, such as movie ticket sales, snack purchases, and reservation cancellations. It also manages the reading and writing of movie, reservation, ticket, and snack data to and from files.

Responsibilities:
Handle movie ticket sales and snack purchases.
Manage reservation cancellations.
Read and write customer-related data.

2. Hall Class
Description: The Hall class represents movie halls in a cinema, enabling seat reservations, information retrieval, and displaying available seats.

Responsibilities:
Enable seat reservations.
Retrieve hall information.
Display available seats.

Kids Hall Class
Description: Provides a specialized representation of a hall tailored for children's events, offering unique features and functionality while inheriting common traits from the Hall class.

Responsibilities:
Manage children's event halls with specialized features.
Standard Hall Class

Description: Offers a fundamental depiction of a hall available at a more affordable price range.

Responsibilities:
Manage standard halls with basic features.

VIP Hall Class
Description: Offers a specialized and high-end portrayal of a hall, tailored to cater to the requirements and standards of VIP guests or occasions.

Responsibilities:
Manage VIP halls with premium features.

3. Reservation Class
Description: Designed to obtain reservation details, including the movie title, hall type, and information about the reserved seat.

Responsibilities:
Manage reservation details.

4. Seat Class
Description: Responsible for reserving a seat, retrieving its column and row coordinates, and verifying its reservation status.

Responsibilities:
Reserve seats.
Retrieve seat coordinates.
Verify reservation status.

5. Person Class
Description: Focuses on managing account-related data, overseeing registration and authentication procedures, and handling supplementary information linked to each individual's account.

Responsibilities:
Manage account-related data.
Oversee registration and authentication.
