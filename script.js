// ====== DATA ====== //
const menuItems = [
    { id: 1, name: 'Burger', description: 'Freshly made • Veg friendly', price: 50, rating: 4.4, emoji: '🍔' },
    { id: 2, name: 'Pizza', description: 'Freshly made • Veg friendly', price: 120, rating: 4.5, emoji: '🍕' },
    { id: 3, name: 'Sandwich', description: 'Freshly made • Veg friendly', price: 40, rating: 4.6, emoji: '🥪' },
    { id: 4, name: 'Coffee', description: 'Freshly made • Veg friendly', price: 60, rating: 4.7, emoji: '☕' },
    { id: 5, name: 'Pasta', description: 'Freshly made • Veg friendly', price: 90, rating: 4.4, emoji: '🍝' },
    { id: 6, name: 'Biryani', description: 'Freshly made • Spicy', price: 110, rating: 4.6, emoji: '🍚' },
    { id: 7, name: 'Samosa', description: 'Crispy • Veg friendly', price: 15, rating: 4.5, emoji: '🥟' },
    { id: 8, name: 'Dosa', description: 'Freshly made • South Indian', price: 50, rating: 4.7, emoji: '🥘' },
];

let currentOrder = {
    items: [],
    location: 'Canteen',
    urgency: 20,
    name: ''
};

let allOrders = [];
let orderCounter = 1;

// ====== INITIALIZATION ====== //
document.addEventListener('DOMContentLoaded', () => {
    loadMenuItems();
    updateOrderSummary();
});

// ====== MENU ====== //
function loadMenuItems() {
    const menuGrid = document.getElementById('menu-grid');
    menuGrid.innerHTML = '';
    
    menuItems.forEach(item => {
        const card = document.createElement('div');
        card.className = 'menu-card';
        card.innerHTML = `
            <div class="menu-card-image">${item.emoji}</div>
            <div class="menu-card-header">
                <h4 class="menu-card-name">${item.name}</h4>
                <span class="menu-card-price">₹${item.price}</span>
            </div>
            <p class="menu-card-description">${item.description}</p>
            <div class="menu-card-footer">
                <div class="menu-card-rating">
                    <span class="star">★</span>
                    <span>${item.rating}</span>
                </div>
                <button class="add-btn" onclick="addItemToOrder(${item.id})">ADD</button>
            </div>
        `;
        menuGrid.appendChild(card);
    });
}

// ====== ORDER MANAGEMENT ====== //
function addItemToOrder(itemId) {
    const item = menuItems.find(m => m.id === itemId);
    const existingItem = currentOrder.items.find(i => i.id === itemId);
    
    if (existingItem) {
        existingItem.qty += 1;
    } else {
        currentOrder.items.push({
            id: itemId,
            name: item.name,
            price: item.price,
            qty: 1
        });
    }
    
    updateOrderSummary();
}

function removeItemFromOrder(itemId) {
    currentOrder.items = currentOrder.items.filter(i => i.id !== itemId);
    updateOrderSummary();
}

function updateQty(itemId, change) {
    const item = currentOrder.items.find(i => i.id === itemId);
    if (item) {
        item.qty += change;
        if (item.qty <= 0) {
            removeItemFromOrder(itemId);
        } else {
            updateOrderSummary();
        }
    }
}

function updateOrderSummary() {
    const itemsCount = document.getElementById('items-count');
    const orderItems = document.getElementById('order-items');
    const totalPrice = document.getElementById('total-price');
    const priorityScore = document.getElementById('priority-score');
    const orderQueue = document.getElementById('order-queue');
    
    // Update items count
    const count = currentOrder.items.reduce((sum, item) => sum + item.qty, 0);
    itemsCount.textContent = count;
    
    // Update items list
    if (currentOrder.items.length === 0) {
        orderItems.innerHTML = '<p class="add-items-hint">Add items to get started.</p>';
    } else {
        orderItems.innerHTML = currentOrder.items.map(item => `
            <div class="order-item">
                <div>
                    <div class="order-item-name">${item.name}</div>
                    <span style="color: var(--text-light);">₹${item.price}</span>
                </div>
                <div class="order-item-qty">
                    <button class="qty-btn" onclick="updateQty(${item.id}, -1)">−</button>
                    <span style="width: 20px; text-align: center;">${item.qty}</span>
                    <button class="qty-btn" onclick="updateQty(${item.id}, 1)">+</button>
                </div>
            </div>
        `).join('');
    }
    
    // Calculate total price
    const total = currentOrder.items.reduce((sum, item) => sum + (item.price * item.qty), 0);
    totalPrice.textContent = '₹' + total;
    
    // Calculate priority score (price + urgency)
    const priority = calculatePriority(total, currentOrder.urgency);
    priorityScore.textContent = priority;
    
    // Update order queue
    orderQueue.textContent = allOrders.length + ' order(s) in queue';
}

function calculatePriority(price, urgency) {
    // Simple priority calculation: higher price and urgency = higher priority
    return Math.floor((price / 100) * 10 + urgency);
}

function selectLocation(btn, location) {
    // Update active button
    document.querySelectorAll('.location-btn').forEach(b => b.classList.remove('active'));
    btn.classList.add('active');
    
    // Update current order
    currentOrder.location = location;
}

function updateUrgency(value) {
    currentOrder.urgency = parseInt(value);
    document.getElementById('urgency-num').textContent = value;
    updateOrderSummary();
}

function placeOrder() {
    // Validate order
    if (currentOrder.items.length === 0) {
        alert('Please add at least one item to your order');
        return;
    }
    
    // Get customer name - use generated name if prompt not available
    const name = `Customer_${orderCounter}`;
    currentOrder.name = name;
    
    // Create order object
    const totalPrice = currentOrder.items.reduce((sum, item) => sum + (item.price * item.qty), 0);
    const priority = calculatePriority(totalPrice, currentOrder.urgency);
    
    const order = {
        id: orderCounter++,
        name: currentOrder.name,
        location: currentOrder.location,
        items: [...currentOrder.items],
        totalPrice: totalPrice,
        priority: priority,
        urgency: currentOrder.urgency,
        timestamp: new Date().toLocaleTimeString(),
        delivered: 0
    };
    
    allOrders.push(order);
    
    // Reset form
    currentOrder.items = [];
    currentOrder.urgency = 20;
    document.getElementById('urgency-slider').value = 20;
    document.getElementById('urgency-num').textContent = '20';
    
    // Reset location
    const locationBtns = document.querySelectorAll('.location-btn');
    locationBtns.forEach(btn => btn.classList.remove('active'));
    locationBtns[0].classList.add('active');
    currentOrder.location = 'Canteen';
    
    updateOrderSummary();
    
    alert(`Order placed successfully! Order ID: #${order.id}`);
    
    // Auto switch to orders tab
    switchTab('orders');
}

// ====== TABS ====== //
function switchTab(tabName, btn) {
    document.querySelectorAll('.tab-content').forEach(tab => {
        tab.classList.remove('active');
    });

    document.querySelectorAll('.nav-btn').forEach(b => {
        b.classList.remove('active');
    });

    document.getElementById(tabName + '-tab').classList.add('active');

    if (btn) btn.classList.add('active');

    if (tabName === 'orders') displayOrders();
}

// ====== ORDERS TAB ====== //
function displayOrders() {
    const ordersList = document.getElementById('orders-list');
    const ordersCount = document.getElementById('orders-count');
    
    // Update count
    ordersCount.textContent = allOrders.length + ' order(s) in the system';
    
    // Display orders
    if (allOrders.length === 0) {
        ordersList.innerHTML = `
            <div class="empty-state">
                <div class="empty-icon">📦</div>
                <p class="empty-text">No orders yet</p>
                <a href="#" onclick="switchTab('order'); return false;" class="browse-link">Browse menu</a>
            </div>
        `;
    } else {
        ordersList.innerHTML = allOrders.map((order, idx) => `
            <div class="order-card" style="border: 1px solid #E8E8E8; border-radius: 8px; padding: 16px; margin-bottom: 12px;">
                <div style="display: flex; justify-content: space-between; margin-bottom: 12px;">
                    <div>
                        <h4 style="margin: 0; font-weight: 600;">#${order.id} - ${order.name}</h4>
                        <p style="margin: 4px 0 0 0; font-size: 12px; color: #666;">📍 ${order.location} | 🕐 ${order.timestamp}</p>
                    </div>
                    <span style="background: ${order.delivered ? '#27AE60' : '#FF9500'}; color: white; padding: 4px 12px; border-radius: 12px; font-size: 12px; font-weight: 600;">
                        ${order.delivered ? '✓ Delivered' : 'Pending'}
                        ${order.delivered ? `<div style="font-size:12px;">⏱ ${getDeliveryTime(order.location)} mins</div>` : ''}
                    </span>
                </div>
                <div style="background: #F5F5F5; padding: 12px; border-radius: 6px; margin-bottom: 12px;">
                    ${order.items.map(item => `<div style="font-size: 13px; margin: 4px 0;">${item.name} × ${item.qty} = ₹${item.price * item.qty}</div>`).join('')}
                </div>
                <div style="display: grid; grid-template-columns: 1fr 1fr; gap: 12px; font-size: 12px;">
                    <div><span style="color: #666;">Total:</span> <strong>₹${order.totalPrice}</strong></div>
                    <div><span style="color: #666;">Priority:</span> <strong>${order.priority}</strong></div>
                </div>
            </div>
        `).join('');
    }
}

// ====== PROCESS ORDERS ====== //
function processOrders() {

    allOrders.forEach(o => o.delivered = 0);

    const deliveryBoys = parseInt(document.getElementById('delivery-boys').value) || 5;
    const capacity = parseInt(document.getElementById('capacity').value) || 5;
    const output = document.getElementById('process-output');

    if (allOrders.length === 0) {
        output.textContent = 'No orders to process!';
        return;
    }

    let result = '';

    // ================= SORTING =================
    result += '=====================================\n';
    result += '       SORTING BY PRIORITY\n';
    result += '=====================================\n\n';

    const sortedOrders = [...allOrders].sort((a, b) => b.priority - a.priority);

    sortedOrders.forEach(order => {
        result += `Order #${order.id} | Priority: ${order.priority} | ${order.location}\n`;
    });

    result += '\n';

    // ================= KNAPSACK =================
    result += '=====================================\n';
    result += '     KNAPSACK OPTIMIZATION\n';
    result += '=====================================\n';
    result += `Capacity: ${capacity} items\n`;
    result += '-------------------------------------\n\n';

    let batches = [];
    let used = new Set();

    const distMap = {
        'Canteen': 0,
        'HostelA': 2,
        'HostelB': 4,
        'HostelC': 6
    };

    for (let i = 0; i < sortedOrders.length; i++) {

        if (used.has(sortedOrders[i].id)) continue;

        let location = sortedOrders[i].location;
        let batchOrders = [];
        let totalWeight = 0;

        result += `Checking Location: ${location}\n`;

        for (let j = i; j < sortedOrders.length; j++) {
            if (!used.has(sortedOrders[j].id) &&
                sortedOrders[j].location === location) {

                let weight = sortedOrders[j].items.reduce((s, it) => s + it.qty, 0);
                totalWeight += weight;
                batchOrders.push(sortedOrders[j]);
            }
        }

        result += `Total Items: ${totalWeight}\n`;

        if (totalWeight <= capacity) {

            result += `Status: SELECTED\n`;

            batchOrders.forEach(o => {
                o.delivered = 1;
                used.add(o.id);
                result += `  • Order #${o.id}\n`;
            });

            result += `Load: ${totalWeight}/${capacity}\n`;

            batches.push({
                orders: batchOrders,
                load: totalWeight,
                location: location
            });

        } else {
            result += `Status: SKIPPED (Too large batch)\n`;
        }

        result += '-------------------------------------\n';
    }

    result += `\nTotal Batches: ${batches.length}\n\n`;

    // ================= DELIVERY ASSIGNMENT =================
    result += '=====================================\n';
    result += '    DELIVERY BOY ASSIGNMENT\n';
    result += '=====================================\n\n';

    batches.forEach((batch, idx) => {

        let rider = (idx % deliveryBoys) + 1;

        result += `Batch ${idx + 1} → Rider ${rider}\n`;
        result += `Location: ${batch.location}\n`;

        batch.orders.forEach(o => {
            result += `  • Order #${o.id}\n`;
        });

        result += `Load: ${batch.load}\n`;

        // 🔥 DELIVERY TIME HERE
        result += `Delivery Time: ${distMap[batch.location]} mins\n`;

        result += '-------------------------------------\n';
    });

    result += '\n=====================================\n';
    result += '✓ All orders processed successfully!\n';

    output.innerHTML = `<pre>${result}</pre>`;

    displayOrders();
}

// ====== UTILITIES ====== //
function formatTime(date) {
    return date.toLocaleTimeString();
}

function getDeliveryTime(loc) {
    const map = {
        'Canteen': 0,
        'HostelA': 2,
        'HostelB': 4,
        'HostelC': 6
    };
    return map[loc] || 0;
}
