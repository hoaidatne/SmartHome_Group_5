const container = document.querySelector(".container");
// Menu 1
const menu = document.querySelector(".navbar__links");
const menuButton = document.querySelector(".navbar__icons");
const overlay = document.querySelector("#overlay");
// Menu 2
const menu2 = document.querySelector(".navbar2");
const menuButton2 = document.querySelector(".navbar__icons2");
// Home Button và Room Dropdown
const homeButton = document.getElementById("homeButton");
const dropdown = document.getElementById("roomDropdown");
const roomButtons = document.querySelectorAll(".room-button");
// Date and Time Display
const dateTimeDisplay = document.getElementById("currentDateTime");

// Function to update date and time
function updateDateTime() {
    const now = new Date();
    // Adjust for +07 timezone (7 hours ahead of UTC)
    const offset = 7 * 60; // 7 hours in minutes
    const localTime = new Date(now.getTime() + (offset * 60 * 1000));
    
    const options = {
        weekday: 'long',
        year: 'numeric',
        month: 'long',
        day: 'numeric',
        hour: '2-digit',
        minute: '2-digit',
        second: '2-digit',
        timeZone: 'UTC'
    };
    
    const formattedDateTime = localTime.toLocaleString('en-US', options);
    if (dateTimeDisplay) {
        dateTimeDisplay.textContent = formattedDateTime;
    }
}

// Update date and time every second
if (dateTimeDisplay) {
    updateDateTime();
    setInterval(updateDateTime, 1000);
}

// Xử lý Menu 1 (nếu menuButton tồn tại)
if (menuButton && menu && overlay) {
    menuButton.addEventListener("click", () => {
        menu.classList.toggle("navbar__open");
        menuButton.classList.toggle("open");
        overlay.classList.toggle("show");
    });

    overlay.addEventListener("click", () => {
        menu.classList.toggle("navbar__open");
        menuButton.classList.toggle("open");
        overlay.classList.toggle("show");
    });
}

// Xử lý Menu 2 (nếu menuButton2 tồn tại)
if (menuButton2 && menu2 && overlay) {
    menuButton2.addEventListener("click", () => {
        menu2.classList.toggle("navbar__open");
        menuButton2.classList.toggle("open");
    });
}

// Xử lý Home Button và Room Dropdown
if (homeButton && dropdown) {
    homeButton.addEventListener("click", () => {
        dropdown.classList.toggle("show");
        homeButton.classList.toggle("show");
    });
}

// Xác định phòng hiện tại và làm nổi bật nút tương ứng
if (roomButtons.length > 0) {
    const currentPath = window.location.pathname.toLowerCase();
    let currentRoom;

    // Ánh xạ tên file HTML với data-room
    if (currentPath.includes("index.html")) {
        currentRoom = "Homeroom";
    } else if (currentPath.includes("living_room.html")) {
        currentRoom = "livingroom";
    } else if (currentPath.includes("kitchen.html")) {
        currentRoom = "kitchen";
    } else if (currentPath.includes("bed_room.html")) {
        currentRoom = "bedroom";
    } else if (currentPath.includes("bathroom.html")) {
        currentRoom = "bathroom";
    }

    // Thêm lớp active cho nút phòng hiện tại và xử lý click
    roomButtons.forEach(button => {
        const room = button.getAttribute("data-room");
        if (room === currentRoom) {
            button.classList.add("active");
        }

        // Đóng dropdown khi nhấp vào nút phòng
        button.addEventListener("click", () => {
            dropdown.classList.remove("show");
            homeButton.classList.remove("show");
        });
    });
}

// Ẩn dropdown khi click bên ngoài
document.addEventListener("click", (event) => {
    if (homeButton && dropdown && !homeButton.contains(event.target) && !dropdown.contains(event.target)) {
        dropdown.classList.remove("show");
        homeButton.classList.remove("show");
    }
});