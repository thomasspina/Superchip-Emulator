// Function to parse dropdown options and call loadROM
function getRomOptionsFromDropdown(optionText) {
    let romOptions = JSON.parse(optionText); // Parse JSON from dropdown value
    const romName = romOptions["game"];
    // const cyclesPerFrame = romOptions["cyclesPerFrame"];

    // Call the C++ function via WebAssembly
    Module.ccall("loadROM", null, ["string"], [romName]);
}

// Initialize WebAssembly Module
Module["onRuntimeInitialized"] = function () {
    // Trigger load for the initially selected ROM
    getRomOptionsFromDropdown(document.querySelector("#rom-select").value);

    // Add listener for dropdown changes
    document.querySelector("#rom-select").onchange = function (event) {
        getRomOptionsFromDropdown(event.target.value);
    };
};
