#pragma once

#include <libpq-fe.h>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>

namespace calc_utility {

class PqError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

struct PGconnDeleter {
    void operator()(PGconn* conn) const noexcept;
};

struct PGresultDeleter {
    void operator()(PGresult* result) const noexcept;
};

using pgconn_ptr = std::unique_ptr<PGconn, PGconnDeleter>;
using pgresult_ptr = std::unique_ptr<PGresult, PGresultDeleter>;

class PqResult {
public:
    explicit PqResult(PGresult* res);

    PqResult(const PqResult&) = delete;
    PqResult& operator=(const PqResult&) = delete;

    PqResult(PqResult&&) noexcept = default;
    PqResult& operator=(PqResult&&) noexcept = default;

    ExecStatusType status() const noexcept;
    int rows() const noexcept;
    int cols() const noexcept;
    std::string_view column_name(int col) const;
    bool is_null(int row, int col) const noexcept;
    std::string value(int row, int col) const;
    std::string error_msg() const;
    PGresult* get_handle() noexcept;

private:
    pgresult_ptr res_;
};

class PqShell {
public:
    explicit PqShell(const std::string& conn);

    PqShell(const PqShell&) = delete;
    PqShell& operator=(const PqShell&) = delete;

    PqShell(PqShell&&) noexcept = default;
    PqShell& operator=(PqShell&&) noexcept = default;

    bool is_open() const noexcept;
    PGconn* get_handle() noexcept;
    const PGconn* get_handle() const noexcept;
    std::string error_msg() const;

    PqResult exec(std::string_view sql);

private:
    pgconn_ptr conn_;
};

} // namespace calc_utility