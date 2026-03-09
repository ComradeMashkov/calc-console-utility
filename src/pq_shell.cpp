#include "pq_shell.hpp"

namespace calc_utility {

void PGconnDeleter::operator()(PGconn *conn) const noexcept {
    if (conn)
        PQfinish(conn);
}

void PGresultDeleter::operator()(PGresult *result) const noexcept {
    if (result)
        PQclear(result);
}

PqResult::PqResult(PGresult *res) : res_(res) {
    if (!res_)
        throw PqError("Failed to allocate PGresult!");
}

ExecStatusType PqResult::status() const noexcept {
    return PQresultStatus(res_.get());
}

int PqResult::rows() const noexcept {
    return PQntuples(res_.get());
}

int PqResult::cols() const noexcept {
    return PQnfields(res_.get());
}

std::string_view PqResult::column_name(int col) const {
    return PQfname(res_.get(), col);
}

bool PqResult::is_null(int row, int col) const noexcept {
    return PQgetisnull(res_.get(), row, col) != 0;
}

std::string PqResult::value(int row, int col) const {
    if (is_null(row, col))
        return {};
    return PQgetvalue(res_.get(), row, col);
}

std::string PqResult::error_msg() const {
    const char *msg = PQresultErrorMessage(res_.get());
    return msg ? std::string(msg) : std::string{};
}

PGresult *PqResult::get_handle() noexcept {
    return res_.get();
}

PqShell::PqShell(const std::string &conn) : conn_(PQconnectdb(conn.c_str())) {
    if (!conn_)
        throw PqError("Failed to allocate PGconn!");

    if (PQstatus(conn_.get()) != CONNECTION_OK)
        throw PqError(PQerrorMessage(conn_.get()));
}

bool PqShell::is_open() const noexcept {
    return conn_ && PQstatus(conn_.get()) == CONNECTION_OK;
}

PGconn *PqShell::get_handle() noexcept {
    return conn_.get();
}

const PGconn *PqShell::get_handle() const noexcept {
    return conn_.get();
}

std::string PqShell::error_msg() const {
    return conn_ ? std::string(PQerrorMessage(conn_.get())) : "No connection";
}

PqResult PqShell::exec(const std::string &sql) {
    PGresult *raw = PQexec(conn_.get(), sql.c_str());
    PqResult result(raw);

    const auto st = result.status();
    if (st != PGRES_COMMAND_OK && st != PGRES_TUPLES_OK) {
        throw PqError(result.error_msg());
    }

    return result;
}

PqResult PqShell::exec_params(const std::string &sql, int nParams, const char *const *values,
                              const int *lengths, const int *formats, int resultFormat) {
    PGresult *raw = PQexecParams(conn_.get(), sql.c_str(), nParams, nullptr, values, lengths,
                                 formats, resultFormat);
    PqResult result(raw);

    const auto st = result.status();
    if (st != PGRES_COMMAND_OK && st != PGRES_TUPLES_OK) {
        throw PqError(result.error_msg());
    }

    return result;
}

} // namespace calc_utility
