/*!
 * Big O notation -> O(1)
 * @param message string
 * @return Constructed message for the logfile
 */
string LogMessage(const std::string& message) {
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    std::ostringstream oss;

    oss << std::put_time(ltm, "[%d/%m/%Y : %H:%M:%S  LCT]  ");
    oss << message;
    return oss.str();
}