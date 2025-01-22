// Function to parse dropdown options and call loadROM
function getRomOptionsFromDropdown(optionText) {
    let romOptions = JSON.parse(optionText); // Parse JSON from dropdown value
    const romName = romOptions["game"];
    // const cyclesPerFrame = romOptions["cyclesPerFrame"];

    // Call the C++ function via WebAssembly
    Module.ccall("loadROM", null, ["string"], [romName]);
}

function applyInvert(optionText) {
    let romOptions = JSON.parse(optionText); // Parse JSON from dropdown value
    const romName = romOptions["game"];
    // const cyclesPerFrame = romOptions["cyclesPerFrame"];

    // Call the C++ function via WebAssembly
    Module.ccall("invert", null, ["string"], [romName]);
}

// Initialize WebAssembly Module
Module["onRuntimeInitialized"] = function () {
    // Trigger load for the initially selected ROM
    getRomOptionsFromDropdown(document.querySelector("#rom-select").value);

    // Add listener for dropdown changes
    document.querySelector("#rom-load").onclick = function (event) {
        getRomOptionsFromDropdown(document.querySelector("#rom-select").value);
    };

    document.querySelector("#invert").onclick = function (event) {
        applyInvert(document.querySelector("#rom-select").value);
    };
};
